pub mod lexer {

    use std::str::FromStr;

    use crate::{tokenkind::TokenKind, util::ModChar, Lexer, Scanner, Token};

    pub fn identifier(lexer: &mut Lexer, chunks: &Vec<u8>) -> Option<Token> {
        let mut ch = lexer.current(chunks).unwrap_or(0);
        let mut buf: String = "".to_string();

        // if ch is a whitespace or an control ch , proceed to the next ch
        if ch.is_ascii_control() || ch.is_ascii_whitespace() {
            lexer.next(chunks).unwrap_or(0); // or nothing
        }

        // if ch is not alphanumeric or starts with $ or _, return none and proceed to next rule
        // NOTE: $ because some languages supports variable names starting with $
        match ch.is_ascii_alnum_or_underscoredollar() {
            false => None,
            true => {
                while ch.is_ascii_alnum_or_underscoredollar() {
                    buf.push(ch as char);
                    match lexer.next(chunks) {
                        Some(x) => ch = x,
                        _ => break,
                    }
                }

                match TokenKind::from_str(&buf.as_str()) {
                    Ok(token_kind) => Some(Token {
                        kind: token_kind,
                        lexeme: buf.clone(),
                        raw: format!("\"{}\"", buf.clone()),
                    }),
                    _ => None,
                }
            }
        }
    }

    pub fn comment(lexer: &mut Lexer, chunks: &Vec<u8>) {
        let mut ch = lexer.current(chunks).unwrap_or(0);
        let mut pch = lexer.peek(chunks).unwrap_or(0);

        // if ch is a whitespace or an control ch , proceed to the next ch
        if ch.is_ascii_control() || ch.is_ascii_whitespace() {
            lexer.next(chunks).unwrap_or(0); // or nothing
        }

        match ch as char == '/' {
            false => return,
            true => {
                match pch as char == '/' {
                    true => {
                        match lexer.next(chunks) {
                            Some(x) => ch = x,
                            _ => return,
                        }

                        while ch as char != '\n' {
                            match lexer.next(chunks) {
                                Some(x) => ch = x,
                                _ => break,
                            }
                        }

                        return;
                    }
                    false => (),
                }

                match pch as char == '*' {
                    true => {
                        lexer.next(chunks).unwrap_or(0);
                        loop {
                            match lexer.next(chunks) {
                                Some(x) => ch = x,
                                _ => break,
                            }
                            match lexer.peek(chunks) {
                                Some(x) => pch = x,
                                _ => break,
                            }
                            if ch as char == '*' && pch as char == '/' {
                                lexer.next(chunks).unwrap_or(0);
                                lexer.next(chunks).unwrap_or(0);
                                break;
                            }
                        }
                        return;
                    }
                    false => (),
                }
                lexer.next(chunks).unwrap_or(0);
            }
        }
    }

    pub fn literal(lexer: &mut Lexer, chunks: &Vec<u8>) -> Option<Token> {
        let mut ch = lexer.current(chunks).unwrap_or(0);
        let qch: u8;
        let mut buf: String = "".to_string();

        // if ch is a whitespace or an control ch , proceed to the next ch
        if ch.is_ascii_control() || ch.is_ascii_whitespace() {
            lexer.next(chunks).unwrap_or(0); // or nothing
        }

        match ch.is_ascii_dble_sngl_bk() {
            false => None,
            true => {
                qch = ch;

                match lexer.next(chunks) {
                    Some(x) => ch = x,
                    _ => return None,
                }

                while ch != qch {
                    if qch.is_ascii_dble_sngl_bk() && ch as char == '\n' {
                        break;
                    }

                    // checking for escape characters and skipping them , ie. \'
                    match ch == 92 {
                        true => {
                            buf.push(ch as char);
                            match lexer.next(chunks) {
                                Some(x) => ch = x,
                                _ => break,
                            }
                            buf.push(ch as char);
                        }
                        false => buf.push(ch as char),
                    }

                    match lexer.next(chunks) {
                        Some(x) => ch = x,
                        _ => break,
                    }
                }
                lexer.next(chunks).unwrap_or(0); // or nothing

                Some(Token {
                    kind: TokenKind::Literal,
                    lexeme: buf.clone(),
                    raw: format!("\"{}\"", buf.clone()),
                })
            }
        }
    }

    pub fn punctuation(lexer: &mut Lexer, chunks: &Vec<u8>) -> Option<Token> {
        let ch = lexer.current(chunks).unwrap_or(0);

        // if ch is a whitespace or an control ch , proceed to the next ch
        if ch.is_ascii_control() || ch.is_ascii_whitespace() {
            lexer.next(chunks).unwrap_or(0); // or nothing
        }

        let isnot_punct =
            !ch.is_ascii_punctuation() || ch.is_ascii_dble_sngl_bk() || ch as char == '/';
        match isnot_punct {
            true => None,
            false => {
                lexer.next(chunks).unwrap_or(0);

                match TokenKind::from_str(&(ch as char).to_string()) {
                    Ok(token_kind) => Some(Token {
                        kind: token_kind,
                        lexeme: (ch as char).to_string(),
                        raw: format!("\"{}\"", (ch as char).to_string()),
                    }),
                    _ => None,
                }
            }
        }
    }
    pub fn unknown(lexer: &mut Lexer, chunks: &Vec<u8>) {
        let ch = lexer.current(chunks).unwrap_or(0);
        if ch > 127 {
            lexer.next(chunks).unwrap_or(0); // or nothing
        }
    }
}

pub mod parser {
    use crate::{parser::Parser, syntatic::Syntatic, token::Token, tokenkind::TokenKind};

    // import defaultExport from "module-name";
    // import * as name from "module-name";
    // import { export1 } from "module-name";
    // import { export1 as alias1 } from "module-name";
    // import { default as alias } from "module-name";
    // import { export1, export2 } from "module-name";
    // import { export1, export2 as alias2, /* … */ } from "module-name";
    // import { "string name" as alias } from "module-name";
    // import defaultExport, { export1, /* … */ } from "module-name";
    // import defaultExport, * as name from "module-name";
    // import "module-name";
    pub fn js(parser: &mut Syntatic, tokens: &Vec<Token>) -> Option<String> {
        let mut token = parser.current(tokens).unwrap_or(Token::new());

        // import fs from "fs"
        // var fs = require("fs")
        // import fs \n from "fs"
        // import * from "fs"
        // import {fish, goat } from "fs"
        // println!("here token {}", token.lexeme);
        match token.kind {
            TokenKind::Import => {
                match parser.peek(tokens).unwrap_or(Token::new()).kind {
                    TokenKind::Asterik => {
                        parser.next(tokens); // *
                        loop {
                            token = parser.next(tokens).unwrap_or(Token::new()); //  } "fs" from
                            match token.kind {
                                TokenKind::Literal => (),
                                TokenKind::From => {
                                    token = parser.next(tokens).unwrap_or(Token::new()); // "fs"
                                    return Some(token.lexeme);
                                }
                                _ => return None,
                            }
                        }
                    }
                    TokenKind::OpenCurly => {
                        parser.next(tokens); // {
                        loop {
                            token = parser.next(tokens).unwrap_or(Token::new()); //  } , "fs" , from
                            match token.kind {
                                TokenKind::Comma => (),
                                TokenKind::CloseCurly => (),
                                TokenKind::Literal => (),
                                TokenKind::From => {
                                    token = parser.next(tokens).unwrap_or(Token::new()); // "fs"
                                    return Some(token.lexeme);
                                }
                                _ => return None,
                            }
                        }
                    }
                    TokenKind::Comma => {
                        parser.next(tokens); // ,
                        loop {
                            token = parser.next(tokens).unwrap_or(Token::new()); // from, *, \, , {},
                            match token.kind {
                                TokenKind::Comma => (),
                                TokenKind::OpenCurly => (),
                                TokenKind::CloseCurly => (),
                                TokenKind::Asterik => (),
                                TokenKind::From => {
                                    token = parser.next(tokens).unwrap_or(Token::new()); // "fs"
                                    return Some(token.lexeme);
                                }
                                _ => return None,
                            }
                        }
                    }
                    TokenKind::From => {
                        parser.next(tokens); // from
                        token = parser.next(tokens).unwrap_or(Token::new()); // "fs"
                        match token.kind {
                            TokenKind::Literal => return Some(token.lexeme),
                            _ => return None,
                        }
                    }
                    TokenKind::Literal => {
                        token = parser.next(tokens).unwrap_or(Token::new()); // "fs"
                        match token.kind {
                            TokenKind::Literal => Some(token.lexeme),
                            _ => None,
                        }
                    }

                    _ => {
                        parser.next(tokens);
                        None
                    }
                }
            }
            TokenKind::Require => {
                match parser.peek(tokens).unwrap().kind {
                    TokenKind::OpenParen => {
                        parser.next(tokens); // (
                        token = parser.next(tokens).unwrap(); // "fs"
                        match token.kind {
                            TokenKind::Literal => Some(token.lexeme),
                            _ => None,
                        }
                    }
                    _ => {
                        parser.next(tokens);
                        None
                    }
                }
            }
            _ => {
                parser.next(tokens);
                None
            }
        }
    }

    // import java.util.*;
    // import java.util.FS;
    // pub fn java() -> Option<String> {
    //     None
    // }

    // pub fn python() -> Option<String> {
    //     None
    // }

    // // #include "fs"
    // // #include <fs>
    // pub fn c_cpp() -> Option<String> {
    //     None
    // }
    // pub fn ruby() -> Option<String> {
    //     None
    // }

    // pub fn unknown() {}
}

// parse every supported language to see if lexer is working correctly
// before you implement these
