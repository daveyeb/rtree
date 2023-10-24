use blob::{Blob, File};
use parse::Parse;
use rayon::prelude::{IntoParallelRefIterator, ParallelIterator};
use scan::Scan;
use serde::{Deserialize, Serialize};
use wasm_bindgen::{prelude::*, JsValue};

pub use wasm_bindgen_rayon::init_thread_pool;

mod blob;
mod modchar;
mod parse;
mod scan;
mod token;

#[wasm_bindgen]
extern "C" {
    // Use `js_namespace` here to bind `console.log(..)` instead of just
    // `log(..)`
    #[wasm_bindgen(js_namespace = console)]
    fn log(s: &str);

}

/// Simple JSON serialization for Github REST
#[derive(Debug, Serialize, Deserialize)]
pub struct Tree {
    tree: Vec<File>,
}

#[wasm_bindgen]
pub async fn get_map(tree: JsValue) -> JsValue {
    let host_url = "http://localhost:9000";
    let deser_tree: Tree = serde_wasm_bindgen::from_value(tree.clone()).unwrap();
    let mut blob_contents = Vec::new();

    log(&format!("Prepping blobs"));

    let blobs = deser_tree
        .tree
        .iter()
        .map(|file| Blob::new(file))
        .collect::<Vec<_>>();

    log(&format!("Getting blobs'contents"));
    for b in blobs {
      match b.get_content(host_url).await {
          Some(content) => blob_contents.push((b, content)),
          None => (),
      }
  }

    log(&format!("Parsing blobs"));

    let blob_stmts = blob_contents
        .par_iter()
        .map(|bc| {
            (bc.0.clone(), Scan::from_encoded_str(&bc.1).scan())
        })
        .map(|bt| {
            Parse::from_tokens(bt.1).parse(&bt.0)
        }).filter(|v| !v.is_empty())
        .collect::<Vec<_>>();


    JsValue::from_str(&format!("Done parsing {:?}", blob_stmts))
}

