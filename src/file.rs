use std::str::FromStr;

use crate::{filekind::FileKind};

#[derive(Clone)]
pub struct File {
    pub kind: FileKind,
    pub base_name: String,
    pub ext: String,
}

impl File {
    pub fn from_str(filename: &str) -> Option<File> {
        let splits = filename.split("/").last().unwrap().split(".").collect::<Vec<&str>>();
       
        println!("debug format {:?}", splits);

        match splits.len() {
            2 => match FileKind::from_str(splits[1]) {
                Ok(file_kind) => Some(File {
                    kind: file_kind,
                    base_name: splits[0].to_string(),
                    ext: splits[1].to_string(),
                }),
                _ => None,
            },
            // for example TypeScript definition file extension
            3 => match FileKind::from_str(splits[1]) {
                Ok(file_kind) => Some(File {
                    kind: file_kind,
                    base_name: splits[0].to_string(),
                    ext: splits[1].to_string() + &splits[2].to_string(),
                }),
                _ => None,
            },
            _ => None,
        }
    }
}
