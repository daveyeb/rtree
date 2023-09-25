use std::collections::HashMap;

use crate::{
    blob::Blob,
    scan::Scan,
    token::{Token, TokenKind},
};

#[derive(Debug)]
pub(crate) struct Parse {
    index: usize,
    tokens: Vec<Token>,
}

impl Parse {
    pub fn new() -> Parse {
        Parse {
            index: 0,
            tokens: Vec::new(),
        }
    }

    fn is_end(&self) -> bool {
        self.index + 1 >= self.tokens.len()
    }

    fn current(&self) -> Option<Token> {
        if self.tokens.len() <= self.index {
            return None;
        }
        Some(self.tokens[self.index].clone())
    }

    fn peek(&self) -> Option<Token> {
        if self.tokens.len() <= self.index + 1 {
            return None;
        }
        Some(self.tokens[self.index + 1].clone())
    }

    fn next(&mut self) -> Option<Token> {
        if self.tokens.len() > self.index {
            self.index += 1
        }

        if self.tokens.len() <= self.index {
            return None;
        }
        Some(self.tokens[self.index].clone())
    }

    fn from_tokens(&mut self, tokens: Vec<Token>) {
        self.tokens = tokens;
        self.reset()
    }

    fn reset(&mut self) {
        self.index = 0
    }

    pub fn parse(&mut self, file_tokens: (&Blob, Vec<Token>)) -> Vec<(String, Blob)> {
        self.from_tokens(file_tokens.1);
        let mut blobs = Vec::new();

        loop {
            // println!("anyt");
            match js(self) {
                Some(x) => {
                    // println!("{} -> {}", x, self.blob.path.to_string());
                    blobs.push((x, file_tokens.0.clone()));
                }
                _ => (),
            }

            if self.is_end() {
                break;
            }
        }

        blobs
    }
}

fn js(parser: &mut Parse) -> Option<String> {
    let mut token = parser.current().unwrap_or_default();

    // import fs from "fs"
    // var fs = require("fs")
    // import fs \n from "fs"
    // import * from "fs"
    // import {fish, goat } from "fs"
    // println!("here token {}", token.lexeme);
    match token.kind() {
        TokenKind::Import => {
            match parser.peek().unwrap_or_default().kind() {
                TokenKind::Asterik => {
                    parser.next(); // *
                    loop {
                        token = parser.next().unwrap_or_default(); //  } "fs" from
                        match token.kind() {
                            TokenKind::Literal => (),
                            TokenKind::From => {
                                token = parser.next().unwrap_or_default(); // "fs"
                                return Some(token.lexeme());
                            }
                            _ => return None,
                        }
                    }
                }
                TokenKind::OpenCurly => {
                    parser.next(); // {
                    loop {
                        token = parser.next().unwrap_or_default(); //  } , "fs" , from
                        match token.kind() {
                            TokenKind::Comma => (),
                            TokenKind::CloseCurly => (),
                            TokenKind::Literal => (),
                            TokenKind::From => {
                                token = parser.next().unwrap_or_default(); // "fs"
                                return Some(token.lexeme());
                            }
                            _ => return None,
                        }
                    }
                }
                TokenKind::Comma => {
                    parser.next(); // ,
                    loop {
                        token = parser.next().unwrap_or_default(); // from, *, \, , {},
                        match token.kind() {
                            TokenKind::Comma => (),
                            TokenKind::OpenCurly => (),
                            TokenKind::CloseCurly => (),
                            TokenKind::Asterik => (),
                            TokenKind::From => {
                                token = parser.next().unwrap_or_default(); // "fs"
                                return Some(token.lexeme());
                            }
                            _ => return None,
                        }
                    }
                }
                TokenKind::From => {
                    parser.next(); // from
                    token = parser.next().unwrap_or_default(); // "fs"
                                                               // print!("lit token here {}", token.lexeme);
                    match token.kind() {
                        TokenKind::Literal => return Some(token.lexeme()),
                        _ => return None,
                    }
                }
                TokenKind::Literal => {
                    token = parser.next().unwrap_or_default(); // "fs"
                    match token.kind() {
                        TokenKind::Literal => Some(token.lexeme()),
                        _ => None,
                    }
                }

                _ => {
                    // print!("none token here {}", token.lexeme);
                    parser.next();
                    None
                }
            }
        }
        TokenKind::Require => {
            match parser.peek().unwrap().kind() {
                TokenKind::OpenParen => {
                    parser.next(); // (
                    token = parser.next().unwrap(); // "fs"
                    match token.kind() {
                        TokenKind::Literal => Some(token.lexeme()),
                        _ => None,
                    }
                }
                _ => {
                    parser.next();
                    None
                }
            }
        }
        _ => {
            // if token.lexeme.ends_with("import") {
            // println!("token none {}", token.lexeme);
            // }
            parser.next();
            None
        }
    }
}
