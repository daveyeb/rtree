use crate::Rules;
use crate::Scanner;
use crate::Token;

pub struct Lexer {
    index: usize, // check if out of bounds
}

impl Lexer {
    pub fn new() -> Lexer {
        Lexer { index: 0 }
    }
}

impl Scanner<Vec<Token>, u8> for Lexer {
    fn current(&self, chunks: &Vec<u8>) -> u8 {
        if chunks.len() == self.index {
            panic!("Error : Lexer::current [index out of bounds in chunks]")
        }
        chunks[self.index]
    }

    fn next(&mut self, chunks: &Vec<u8>) -> u8 {
        self.index += 1;
        if chunks.len() == self.index {
            panic!("Error : Lexer::next [index out of bounds in chunks]")
        }
        chunks[self.index]
    }

    fn peek(&self, chunks: &Vec<u8>) -> Option<u8> {
        if chunks.len() == self.index + 1 {
            return None;
        }
        Some(chunks[self.index + 1])
    }

    fn scan(&mut self, chunks: &Vec<u8>) -> Vec<Token> {
        let mut tokens: Vec<Token> = Vec::new();
        loop {
            match Rules::identifier(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }

            match Rules::punctuation(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }

            match Rules::literal(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }
            
            Rules::comment(self, chunks);
            Rules::unknown(self, chunks);
            break;
        }

        tokens
    }
}
