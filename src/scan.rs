use base64::{engine::general_purpose, Engine as _};

use crate::{token::Token, util::ModifiedChar};

#[derive(Debug)]
pub(crate) struct Scan {
    index: usize,
    chunks: Vec<u8>
}

impl Scan {
    pub(crate) fn new() -> Scan {
        Scan {
            index: 0,
            chunks: Vec::new()
        }
    }

    pub(crate) fn from_encoded(&mut self, chunk: &str) {
        let decoded = general_purpose::STANDARD
            .decode(chunk.replace("\n", ""))
            .unwrap();

        self.reset();
        self.chunks = decoded;
    }

    fn reset(&mut self) {
        self.index = 0
    }

    fn next(&mut self) -> Option<u8> {
        if self.chunks.len() > self.index {
            self.index += 1
        }

        if self.chunks.len() <= self.index {
            return None;
        }
        Some(self.chunks[self.index])
    }

    fn current(&self) -> Option<u8> {
        if self.chunks.len() <= self.index {
            return None;
        }
        Some(self.chunks[self.index])
    }

    fn peek(&self) -> Option<u8> {
        if self.chunks.len() <= self.index + 1 {
            return None;
        }
        Some(self.chunks[self.index + 1])
    }

    fn is_end(&self) -> bool {
        self.index + 1 >= self.chunks.len()
    }

    pub fn scan(&mut self, chunk: &str) -> Vec<Token> {
        let mut tokens: Vec<Token> = Vec::new();
        self.from_encoded(chunk);

        loop {
            match identifier(self) {
                Some(x) => tokens.push(x),
                None => (),
            }
            match punctuation(self) {
                Some(x) => tokens.push(x),
                None => (),
            }

            match literal(self) {
                Some(x) => tokens.push(x),
                None => (),
            }

            comment(self);
            unknown(self);

            if self.is_end() {
                break;
            }
        }

        tokens
    }
}

fn identifier(lexer: &mut Scan) -> Option<Token> {
    let mut buf = format!("");
    let mut ch = lexer.current().unwrap_or_default();

    if ch.is_ascii_control() || ch.is_ascii_whitespace() {
        lexer.next();
    }

    // if ch is not alphanumeric or starts with $ or _, return none and proceed to next rule
    // NOTE: $ because some languages supports variable names starting with $
    match ch.is_u8_alnum_or_under_dollar() {
        false => None,
        true => {
            while ch.is_u8_alnum_or_under_dollar() {
                buf.push(ch as char);
                match lexer.next() {
                    x => ch = x.unwrap_or_default(),
                }
            }
            return Some(Token::new(&buf));
        }
    }
}

fn comment(lexer: &mut Scan) {
    let mut ch = lexer.current().unwrap_or_default(); // idk how its all gonna work out [this or current]
    let mut pch = lexer.peek().unwrap_or_default();

    if ch.is_ascii_control() || ch.is_ascii_whitespace() {
        lexer.next();
    }

    match ch as char == '/' {
        false => return,
        true => {
            match pch as char == '/' {
                true => {
                    match lexer.next() {
                        x => ch = x.unwrap_or_default(),
                    }

                    while ch as char != '\n' {
                        match lexer.next() {
                            x => ch = x.unwrap_or_default(),
                        }
                    }

                    return;
                }
                false => (),
            }

            match pch as char == '*' {
                true => {
                    lexer.next();
                    loop {
                        match lexer.next() {
                            x => ch = x.unwrap_or_default(),
                        }
                        match lexer.peek() {
                            x => pch = x.unwrap_or_default(),
                        }
                        if ch as char == '*' && pch as char == '/' {
                            lexer.next();
                            lexer.next();
                            break;
                        }
                    }
                    return;
                }
                false => (),
            }
            lexer.next();
        }
    }
}

fn literal(lexer: &mut Scan) -> Option<Token> {
    let mut buf = format!("");
    let mut ch = lexer.current().unwrap_or_default();
    let qch: u8;

    if ch.is_ascii_control() || ch.is_ascii_whitespace() {
        // this too is iffy
        lexer.next();
    }

    match ch.is_u8_double_single() {
        false => None,
        true => {
            qch = ch;

            match lexer.next() {
                x => ch = x.unwrap_or_default(),
            }

            while ch != qch {
                if qch.is_u8_double_single() && ch as char == '\n' {
                    break;
                }

                // checking for escape characters and skipping them , ie. \'
                match ch == 92 {
                    true => {
                        buf.push(ch as char);
                        match lexer.next() {
                            x => ch = x.unwrap_or_default(),
                            _ => break,
                        }
                        buf.push(ch as char);
                    }
                    false => buf.push(ch as char),
                }

                match lexer.next() {
                    x => ch = x.unwrap_or_default(),
                }
            }
            lexer.next(); // or nothing

            Some(Token::as_literal(&buf))
        }
    }
}

fn punctuation(lexer: &mut Scan) -> Option<Token> {
    let ch = lexer.current().unwrap_or_default();

    if ch.is_ascii_control() || ch.is_ascii_whitespace() {
        // this too is iffy
        lexer.next();
    }

    let invalid_punct = !ch.is_ascii_punctuation() || ch.is_u8_double_single() || ch as char == '/';
    match invalid_punct {
        true => None,
        false => {
            lexer.next();

            return Some(Token::new(&(ch as char).to_string()));
        }
    }
}

fn unknown(lexer: &mut Scan) {
    // limited unicode
    let ch = lexer.current().unwrap_or_default();
    if ch > 127 {
        lexer.next();
    }
}
// error handling
// print display
