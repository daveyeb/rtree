use serde::{Deserialize, Serialize};
use std::ffi::OsStr;
use std::path::Path;
use std::str::FromStr;
use strum_macros::EnumString;


#[derive(Debug, Clone, Serialize, Deserialize)]
struct BlobContent {
    content: String,
}

#[derive(Debug, Serialize, EnumString, Default, Clone)]
pub enum Blob {
    // (path, contents)
    #[strum(serialize = "java")]
    Java(String, String),
    #[strum(serialize = "js", serialize = "ts")]
    JavaScript(String, String),
    #[strum(serialize = "py")]
    Python(String, String),
    #[strum(serialize = "rs")]
    Rust(String, String),
    #[strum(serialize = "cpp")]
    CPlusPlus(String, String),
    #[strum(serialize = "c")]
    C(String, String),
    #[strum(serialize = "go")]
    GoLang(String, String),
    #[default]
    Unknown,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct File {
    path: String,
    r#type: String,
    url: String,
}

impl Blob {
    pub fn new(file: &File) -> Self {
        if file.r#type != "blob" {
            return Blob::Unknown;
        }
        let ext = Self::ext(&file.path).unwrap_or("");
        match Blob::from_str(ext) {
            Ok(b) => match b {
                Blob::C(_, _) => Blob::C(file.path.clone(), file.url.clone()),
                Blob::Java(_, _) => Blob::Java(file.path.clone(), file.url.clone()),
                Blob::Rust(_, _) => Blob::Rust(file.path.clone(), file.url.clone()),
                Blob::Python(_, _) => Blob::Python(file.path.clone(), file.url.clone()),
                Blob::GoLang(_, _) => Blob::GoLang(file.path.clone(), file.url.clone()),
                Blob::JavaScript(_, _) => Blob::JavaScript(file.path.clone(), file.url.clone()),
                Blob::CPlusPlus(_, _) => Blob::CPlusPlus(file.path.clone(), file.url.clone()),
                _ => todo!(),
            },
            Err(_) => Blob::Unknown,
        }
    }

    // host url http://localhost:9000
    pub async fn get_content(&self, host_url: &str) -> Option<String> {
        match self.url() {
            Some(url) => {
                let content = reqwest_wasm::get(&format!("{}/blob?url={}", host_url, url))
                    .await
                    .unwrap()
                    .text()
                    .await
                    .unwrap();


                Some(content)
            }
            _ => None,
        }
    }

    // fn ext(&self) -> Option<String> {
    //     match self {
    //         Blob::Java(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::JavaScript(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::Python(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::Rust(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::CPlusPlus(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::C(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         Blob::GoLang(x, _) => Some(x.rsplit_once(".").unwrap().1.to_string()),
    //         _ => None,
    //     }
    // }

    fn ext(path: &str) -> Option<&str> {
        Path::new(path).extension().and_then(OsStr::to_str)
    }

    fn url(&self) -> Option<String> {
        match self {
            Blob::Java(_, x) => Some(x.to_string()),
            Blob::JavaScript(_, x) => Some(x.to_string()),
            Blob::Python(_, x) => Some(x.to_string()),
            Blob::Rust(_, x) => Some(x.to_string()),
            Blob::CPlusPlus(_, x) => Some(x.to_string()),
            Blob::C(_, x) => Some(x.to_string()),
            Blob::GoLang(_, x) => Some(x.to_string()),
            _ => None,
        }
    }

    // async fn content(&self, url: &str) -> Option<String> {
    //     match self {
    //         Blob::Java(_, _) => Some(self.get_content(url).await),
    //         Blob::JavaScript(_, _) => Some(self.get_content(url).await),
    //         Blob::Python(_, _) => Some(self.get_content(url).await),
    //         Blob::Rust(_, _) => Some(self.get_content(url).await),
    //         Blob::CPlusPlus(_, _) => Some(self.get_content(url).await),
    //         Blob::C(_, _) => Some(self.get_content(url).await),
    //         Blob::GoLang(_, _) => Some(self.get_content(url).await),
    //         _ => None,
    //     }
    // }
}
