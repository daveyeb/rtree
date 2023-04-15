use crate::file::File;
use crate::parser::Parser;
use crate::rules::parser;
use crate::Token;
use std::collections::HashMap;

pub struct Syntatic {
    index: usize,
}

impl Syntatic {
    pub fn new() -> Syntatic {
        Syntatic { index: 0 }
    }

    pub fn is_end(&self, len: usize) -> bool {
        self.index + 1 >= len
    }
}

impl Parser<File, Token> for Syntatic {
    fn current(&self, tokens: &Vec<Token>) -> Option<Token> {
        if tokens.len() <= self.index {
            return None;
        }
        Some(tokens[self.index].clone())
    }

    fn peek(&self, tokens: &Vec<Token>) -> Option<Token> {
        if tokens.len() <= self.index + 1 {
            return None;
        }
        Some(tokens[self.index + 1].clone())
    }

    fn next(&mut self, tokens: &Vec<Token>) -> Option<Token> {
        if tokens.len() > self.index {
            self.index += 1
        }

        if tokens.len() <= self.index {
            return None;
        }
        Some(tokens[self.index].clone())
    }

    fn parse(&mut self, deps: &mut HashMap<String, String>, file_tokens: (&File, &Vec<Token>)) {
        self.index = 0;
        let (file, tokens) = file_tokens;

        loop {
            match parser::js(self, tokens) {
                Some(x) => {
                    deps.insert(x, file.base_name.clone());
                }
                _ => (),
            }

            if self.is_end(tokens.len()) {
                break;
            }
        }
    }
}
