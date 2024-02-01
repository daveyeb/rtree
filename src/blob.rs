use serde::{Deserialize, Serialize};
use std::str::FromStr;
use strum_macros::EnumString;

#[derive(Debug, PartialEq, EnumString, Clone, Default, Eq, Hash)]
pub enum BlobKind {
    #[strum(serialize = "java")]
    Java,
    #[strum(serialize = "js", serialize = "ts")]
    JavaScript,
    #[strum(serialize = "py")]
    Python,
    #[strum(serialize = "rs")]
    Rust,
    #[strum(serialize = "cpp")]
    CPlusPlus,
    #[strum(serialize = "c")]
    C,
    #[strum(serialize = "go")]
    GoLang,
    #[default]
    Unknown,
}

#[derive(Debug, Clone, Serialize, Deserialize, Eq, Hash, PartialEq)]
pub(crate) struct Blob {
    pub path: String,
    pub url: String,
    pub r#type: String,
    #[serde(skip)]
    ext: String,
    #[serde(skip)]
    kind: BlobKind,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct Blobs {
    pub tree: Vec<Blob>,
}

impl Blob {
  pub fn new(name: String) -> Self {

    Blob {
      path: name,
      url: "https://".to_string(),
      r#type: "js".to_string(),
      ext: ".js".to_string(),
      kind: BlobKind::JavaScript
    }
  }
}
