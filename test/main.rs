// use std::{env, fs, path::Path};

// use blob::{Blob, File};
// use parse::Parse;
// use rayon::prelude::{IntoParallelRefIterator, ParallelIterator};
// use scan::Scan;
// use serde::{Deserialize, Serialize};
// use walkdir::WalkDir;
// use wasm_bindgen::prelude::wasm_bindgen;

// extern crate glob;
// use glob::glob;

// mod blob;
// mod modchar;
// mod parse;
// mod scan;
// mod token;

// #[wasm_bindgen]
// extern "C" {
//     // Use `js_namespace` here to bind `console.log(..)` instead of just
//     // `log(..)`
//     #[wasm_bindgen(js_namespace = console)]
//     fn log(s: &str);

// }

// / Simple JSON serialization for Github REST
// #[derive(Debug, Serialize, Deserialize)]
// pub struct Tree {
//     tree: Vec<File>,
// }

// #[tokio::main]
// async fn main() {


//     get_map_three("./").await;
// }

// pub async fn get_map_two(data: &str) {
//     let host_url = "http://localhost:9000";
//     // let deser_tree: Tree = serde_wasm_bindgen::from_value(tree.clone())?;
//     let deser_tree: Tree = serde_json::from_str(data).unwrap();
//     let mut blob_contents = Vec::new();

//     log(&format!("here 1"));

//     let blobs = deser_tree
//         .tree
//         .iter()
//         .map(|file| Blob::new(file))
//         .collect::<Vec<_>>();

//     log(&format!("here 2"));
//     for b in blobs {
//         match b.get_content(host_url).await {
//             Some(content) => blob_contents.push((b, content)),
//             None => (),
//         }
//     }

//     log(&format!("here 3"));

//     let blob_stmts = blob_contents
//         .into_iter()
//         .map(|bc| {
//             log(&format!("{:?}", bc.0));
//             (bc.0.clone(), Scan::from_encoded_str(&bc.1).scan())
//         })
//         .map(|bt| {
//             log(&format!("{:?} parse", bt.0));

//             Parse::from_tokens(bt.1).parse(&bt.0)
//         })
//         .collect::<Vec<_>>();

//     // log(&format!("here 4"));

//     log(&format!("Done parsing {:?}", blob_stmts));
// }

// pub async fn get_map_three(path: &str) {
//   let files = read(path);

//   let blob_stmts = files
//       .par_iter()
//       .map(|bc| {
//           // log(&format!("{:?}", bc.0));
//           (bc.0.clone(), Scan::new(&bc.1).scan())
//       })
//       .map(|bt| {
//           // log(&format!("\n\n{} {:?}", bt.0, bt.1));
//           // println!("parsing {}", bt.0);

//           Parse::from_tokens(bt.1).parse(bt.0)
//       })
//       .filter(|v|!v.is_empty()).collect::<Vec<_>>();

//   log(&format!("\n\nhere 4"));

//   println!("{}", &format!("\n\nDone parsing {:?}", blob_stmts));
// }

// fn log(s: &str) {
//     println!("{}", s);
// }

// fn read(path: &str) -> Vec<(String, String)> {

//     let mut contents = Vec::new();

//     for entry in WalkDir::new(path).into_iter().filter_map(|e| e.ok() ) {
//       if entry.path().is_file() && (entry.path().display().to_string().ends_with("js") || entry.path().display().to_string().ends_with("ts")){
//         print!(".");

//         let content = fs::read_to_string(entry.path().display().to_string()).unwrap_or("".to_string());

//         contents.push((entry.path().display().to_string(), content));
//       }
//     }

//     contents
// }


// # tokio = { version = "1", features = ["full"] }
// # serde_json = "1.0"
// # reqwest = { version = "0.11.19", default-features = false, features = ["rustls-tls", "json"] }
// # glob = "0.3.1"
// # walkdir = "2.4.0"
