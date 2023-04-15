mod file;
mod filekind;
mod lexer;
mod parser;
mod rules;
mod scanner;
mod syntatic;
mod token;
mod tokenkind;
mod util;

use filekind::FileKind;
use lexer::Lexer;
use scanner::Scanner;
use std::fs;
use syntatic::Syntatic;
use token::Token;

use std::collections::HashMap;
use walkdir::WalkDir;

use crate::file::File;
use crate::parser::Parser;

fn main() {
    let mut files: Vec<String> = Vec::new();

    for entry in WalkDir::new("./test/TypeScript/")
        .into_iter()
        .filter_map(Result::ok)
        .filter(|e| !e.file_type().is_dir())
    {
        let f_name = String::from(entry.path().to_string_lossy());
        files.push(f_name);
    }

    let mut lexer = Lexer::new();
    let mut parser = Syntatic::new();
    let mut deps: HashMap<String, String> = HashMap::new();
    let len = files.len();
    let mut file=File { kind: FileKind::Unknown, base_name: "".to_string(), ext: "".to_string() }; 
    
    for f in files {
        print!("File  parsing {}\n", f);

        let chunks = fs::read_to_string(f.clone()).unwrap_or("".to_string());
        match File::from_str(f.as_str()) {
            Some(x) => file = x,
            None => ()
        }
        let chunks = (&file, &chunks.into_bytes());

        // parser.parse(&mut deps, (&f, &tokens));
        let tokens = lexer.scan(chunks);
        let file_tokens = (chunks.0, &tokens);
        parser.parse(&mut deps, file_tokens);
    }

    // per file 
    // let f = "./test/TypeScript/tests/projects/inferredTypeFromTransitiveModule/index.ts";
    // print!("File  parsing {}\n", f);
    // let chunks = fs::read_to_string(f).unwrap_or("".to_string());
    // match File::from_str(f) {
    //     Some(x) => file = x,
    //     None => ()
    // }
    // let chunks = (&file, &chunks.into_bytes());
    // let tokens = lexer.scan(chunks);
    // let file_tokens = (chunks.0, &tokens);
    // parser.parse(&mut deps, file_tokens);

    for (parent, dep) in &deps {
        println!("{} -> {}", parent, dep);
    }

    print!("Program done! files {}\n", len)
}

// Ideas
// glob file directory
//     input file name as keys

// Issues
// rules::comment
//     cant skip over escape sequences when its a new line

// simple questions
// what is difference b/n
// expected tuple `(&file::File, &Vec<u8>)`
//    found tuple `&(file::File, Vec<u8>)`
