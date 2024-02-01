use rayon::prelude::*;
use wasm_bindgen::prelude::*;

use futures_channel::oneshot;
use serde::{Deserialize, Serialize};
use wasm_bindgen_futures::JsFuture;
use web_sys::{Request, RequestInit, RequestMode, Response};
use web_sys::console;
use js_sys::{Promise, Uint8ClampedArray, WebAssembly};

use parse::Parse;
use scan::Scan;
use blob::Blob;

pub use wasm_bindgen_rayon::init_thread_pool;

macro_rules! console_log {
  ($($t:tt)*) => (crate::log(&format_args!($($t)*).to_string()))
}

mod scan;
mod parse;
mod util;
mod blob;
mod token;

#[wasm_bindgen]
extern "C" {
  #[wasm_bindgen(js_namespace = console)]
  fn log(s: &str);
  #[wasm_bindgen(js_namespace = console, js_name = log)]
  fn logv(x: &JsValue);
}

#[derive(Serialize, Deserialize)]
pub struct Element {
    id: u32,
    name: String,
    default_branch: String,
    // parent_id: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct Tree {
  pub tree: Vec<File>,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct File {
  pub path: String,
  pub url: String
}

#[wasm_bindgen]
pub fn scan_repo() -> String {
  let mut scanner = Scan::new();
  let mut parser = Parse::new();

  parser.parse((&Blob::new("file.txt".to_string()), scanner.scan("fish state")));
  "fish".to_string()
}


#[wasm_bindgen]
pub async fn get_repo(repo: String) -> Result<JsValue, JsValue> {
    let repo_split = repo.split("/").collect::<Vec<_>>();

    if repo_split.len() != 2 {
        return Err(JsValue::NULL);
    }

    let default_branch = get_default_branch(repo_split[0], repo_split[1]).await?;
    let tree = get_tree((repo_split[0], repo_split[1]), &default_branch, "ghu_Q5E769Ql6KDhWTUKUhaza6bTUTfpQL3TBxbq").await?;

    let test = tree.par_iter().map(|x|{
      console::log_1(&serde_wasm_bindgen::to_value(&x.path).unwrap())
    });
    test.collect::<Vec<_>>();


    Ok(serde_wasm_bindgen::to_value(&format!("done {:?}", end - start)).unwrap())
}

pub(crate) async fn get_default_branch(owner: &str, repo: &str) -> Result<String, JsValue> {
    let mut opts = RequestInit::new();
    opts.method("GET");
    opts.mode(RequestMode::Cors);

    let url = format!("https://api.github.com/repos/{}/{}", owner, repo);

    let request = Request::new_with_str_and_init(&url, &opts)?;

    let headers = request.headers();
    headers.set("X-GitHub-Api-Version", "2022-11-28")?;
    headers.set("User-Agent", "rtree.rs")?;
    headers.set("Accept", "application/vnd.github.v3+json")?;

    let window = web_sys::window().unwrap();
    let resp_value = JsFuture::from(window.fetch_with_request(&request)).await?;

    // `resp_value` is a `Response` object.
    assert!(resp_value.is_instance_of::<Response>());
    let resp: Response = resp_value.dyn_into().unwrap();

    // Convert this other `Promise` into a rust `Future`.
    let json = JsFuture::from(resp.json()?).await?;
    let ser_json: Element = serde_wasm_bindgen::from_value(json.clone())?;
    // Send the JSON response back to JS.

    Ok(ser_json.default_branch)

    // Ok(json)
    // format!("{}", json["default_branch"].to_string())
}


pub(crate) async fn get_tree(
    owner_repo: (&str, &str),
    sha: &str,
    token: &str,
) -> Result<Vec<File>, JsValue> {
    let mut opts = RequestInit::new();
    opts.method("GET");
    opts.mode(RequestMode::Cors);



    let url = format!(
        "https://api.github.com/repos/{}/{}/git/trees/{}?recursive=1",
        owner_repo.0, owner_repo.1, sha
    );

    console::log_1(&serde_wasm_bindgen::to_value(&url).unwrap());
    // let url = format!("https://api.github.com/repos/{}/{}", owner, repo);

    let request = Request::new_with_str_and_init(&url, &opts)?;

    let headers = request.headers();
    headers.set("X-GitHub-Api-Version", "2022-11-28")?;
    headers.set("User-Agent", "rtree.rs")?;
    headers.set("Accept", "application/vnd.github.v3+json")?;
    headers.set("Authorization", &format!("Bearer {}", token))?;

    let window = web_sys::window().unwrap();
    let resp_value = JsFuture::from(window.fetch_with_request(&request)).await?;

    // `resp_value` is a `Response` object.
    assert!(resp_value.is_instance_of::<Response>());
    let resp: Response = resp_value.dyn_into().unwrap();

    // Convert this other `Promise` into a rust `Future`.
    let json = JsFuture::from(resp.json()?).await?;
    let ser_json: Tree = serde_wasm_bindgen::from_value(json.clone())?;
    // Send the JSON response back to JS.

    Ok(ser_json.tree)

    // Ok(json)
    // format!("{}", json["default_branch"].to_string())
}
