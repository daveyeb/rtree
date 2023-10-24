use crate::{modchar::ModChar, token::Token};
use base64::{engine::general_purpose, Engine as _};

#[derive(Debug)]
pub struct Scan {
    index: usize,
    chunks: Vec<u8>,
}

impl Scan {
    pub fn from_encoded_str(content: &str) -> Self {
        // log(&format!("content {}", content));
        let decoded = general_purpose::STANDARD
            .decode(content.replace("\n", ""))
            .unwrap();

        Scan {
            index: 0,
            chunks: decoded,
        }
    }

    // pub fn new(content: &str) -> Self {
    //     Scan {
    //         index: 0,
    //         chunks: content.into(),
    //     }
    // }

    // scan
    pub fn scan(&mut self) -> Vec<Token> {
        // log(&format!("inside scan"));
        let mut tokens: Vec<Token> = Vec::new();


        loop {
            match identifier(self) {
                Some(x) => {
                    // println!("{}", &format!("token {:?}", x));
                    tokens.push(x)
                }
                None => (),
            }
            match punctuation(self) {
                Some(x) => {
                    // println!("{}", &format!("token {:?}", x));
                    tokens.push(x)
                }
                None => (),
            }

            match literal(self) {
                Some(x) => {
                    // println!("{}", &format!("token {:?}", x));
                    tokens.push(x)
                }
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
                    x => match x {
                        Some(x) => ch = x,
                        None => break,
                    },
                }
            }
            // println!("\n buf {}",buf);
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
                        // print!("c");
                        match lexer.next() {
                            x => match x {
                                Some(x) => ch = x,
                                None => break,
                            },
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
                            x => match x {
                                Some(x) => ch = x,
                                None => break,
                            },
                        }
                        match lexer.peek() {
                            x => match x {
                              Some(x) => pch = x,
                              None => break,
                          },
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
                            x => match x {
                                Some(x) => ch = x,
                                None => break,
                            },
                        }
                        buf.push(ch as char);
                    }
                    false => buf.push(ch as char),
                }

                match lexer.next() {
                    x => match x {
                        Some(x) => ch = x,
                        None => break,
                    },
                }
            }
            lexer.next(); // or nothing

            Some(Token::Literal(buf))
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
