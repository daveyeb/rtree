use crate::{blob::Blob, token::Token};

#[derive(Debug)]
pub struct Parse {
    index: usize,
    tokens: Vec<Token>,
}

impl Parse {
    pub fn from_tokens(t: Vec<Token>) -> Self {
        Parse {
            index: 0,
            tokens: t,
        }
    }

    pub fn parse(&mut self, blob: &Blob) -> Vec<(String, Blob)> {
        let mut stmts = Vec::new();

        loop {
            // println!("anyt");
            match js(self) {
                Some(x) => {
                    // log(&format!("{} -> {:?}", x, blob));
                    stmts.push((x, blob.clone()));
                }
                _ => (),
            }

            // log(".");

            if self.is_end() {
                break;
            }
        }

        stmts
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
}

fn js(parser: &mut Parse) -> Option<String> {
    let mut token = parser.current().unwrap_or_default();

    // import fs from "fs"
    // var fs = require("fs")
    // import fs \n from "fs"
    // import * from "fs"
    // import {fish, goat } from "fs"
    // println!("here token {}", token.lexeme);

    match token {
        Token::Import(_) => {
            match parser.peek().unwrap_or_default() {
                Token::Asterik(_) => {
                    parser.next(); // *
                    loop {
                        token = parser.next().unwrap_or_default(); //  } "fs" from
                        match token {
                            // TODO Mactches should be syntaticly correct eg. import * as ts from  [identifier, from]
                            Token::Literal(_) => (),
                            Token::Identifier(_) => (),
                            Token::From(_) => {
                                token = parser.next().unwrap_or_default(); // "fs"

                                match token {
                                    Token::Literal(_) => return Some(token.lexeme().unwrap()),
                                    _ => return None,
                                }
                            }
                            _ => return None,
                        }
                    }
                }
                Token::OpenCurly(_) => {
                    parser.next(); // {
                    loop {
                        token = parser.next().unwrap_or_default(); //  } , "fs" , from
                                                                   // println!("here from open curly {:?}", token);
                        match token {
                            Token::Comma(_) => (),
                            Token::CloseCurly(_) => (),
                            Token::Literal(_) => (),
                            Token::Identifier(_) => (),
                            Token::From(_) => {
                                token = parser.next().unwrap_or_default(); // "fs"
                                                                           // println!("after from {:?}", token);
                                                                           // return Some(token.lexeme().unwrap());
                                match token {
                                    Token::Literal(_) => return Some(token.lexeme().unwrap()),
                                    _ => return None,
                                }
                            }
                            _ => return None,
                        }
                    }
                }
                Token::Comma(_) => {
                    parser.next(); // ,
                    loop {
                        token = parser.next().unwrap_or_default(); // from, *, \, , {},
                        match token {
                            Token::Comma(_) => (),
                            Token::OpenCurly(_) => (),
                            Token::CloseCurly(_) => (),
                            Token::Asterik(_) => (),
                            Token::From(_) => {
                                // println!("after from comma {:?}", token);
                                token = parser.next().unwrap_or_default(); // "fs"
                                                                           // return Some(token.lexeme().unwrap());
                                match token {
                                    Token::Literal(_) => return Some(token.lexeme().unwrap()),
                                    _ => return None,
                                }
                            }
                            _ => return None,
                        }
                    }
                }
                Token::From(_) => {
                    parser.next(); // from
                    token = parser.next().unwrap_or_default(); // "fs"
                                                               // print!("lit token here {}", token.lexeme);
                    match token {
                        Token::Literal(x) => {
                            // println!("after from from {:?}", x);
                            return Some(x);
                        }
                        _ => return None,
                    }
                }
                Token::Literal(_) => {
                    token = parser.next().unwrap_or_default(); // "fs"
                    match token {
                        Token::Literal(x) => {
                            // println!("after from literal {:?}", x);
                            Some(x)
                        }
                        _ => None,
                    }
                }

                Token::Identifier(_) => {
                    parser.next(); // some identifier
                    loop {
                        token = parser.next().unwrap_or_default(); //  } , "fs" , from
                                                                   // println!("here from id {:?}", token);
                        match token {
                            Token::Comma(_) => (),
                            Token::CloseCurly(_) => (),
                            Token::Literal(_) => (),
                            Token::Identifier(_) => (),
                            Token::From(_) => {
                                token = parser.next().unwrap_or_default(); // "fs"
                                                                           // println!("after from {:?}", token);
                                                                           // return Some(token.lexeme().unwrap());
                                match token {
                                    Token::Literal(_) => return Some(token.lexeme().unwrap()),
                                    _ => return None,
                                }
                            }
                            _ => return None,
                        }
                    }
                }

                _ => {
                    // print!("none token here {}", token.lexeme);
                    parser.next();
                    None
                }
            }
        }
        Token::Require(_) => {
            match parser.peek().unwrap() {
                Token::OpenParen(_) => {
                    parser.next(); // (
                    token = parser.next().unwrap_or_default(); // "fs"
                    match token {
                        Token::Literal(x) => {
                            // println!("after from require {:?}", x);
                            Some(x)
                        }
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
