use crate::file::File;
use crate::rules::lexer;
use crate::Scanner;
use crate::Token;

pub struct Lexer {
    index: usize, // check if out of bounds
}

impl Lexer {
    pub fn new() -> Lexer {
        Lexer { index: 0 }
    }

    pub fn is_end(&self, len: usize) -> bool {
        self.index + 1 >= len
    }
}

impl Scanner<Vec<Token>, u8, File> for Lexer {
    fn current(&self, chunks: &Vec<u8>) -> Option<u8> {
        if chunks.len() <= self.index {
            return None;
        }
        Some(chunks[self.index])
    }

    fn next(&mut self, chunks: &Vec<u8>) -> Option<u8> {
        if chunks.len() > self.index {
            self.index += 1
        }

        if chunks.len() <= self.index {
            return None;
        }
        Some(chunks[self.index])
    }

    fn peek(&self, chunks: &Vec<u8>) -> Option<u8> {
        if chunks.len() <= self.index + 1 {
            return None;
        }
        Some(chunks[self.index + 1])
    }

    fn scan(&mut self, file_chunks: (&File, &Vec<u8>)) -> Vec<Token> {
        self.index = 0;
        let mut tokens: Vec<Token> = Vec::new();
        let (_file, chunks) = file_chunks;

        loop {
            match lexer::identifier(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }

            match lexer::punctuation(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }

            match lexer::literal(self, chunks) {
                Some(x) => tokens.push(x),
                _ => (),
            }

            lexer::comment(self, chunks);
            lexer::unknown(self, chunks);

            if self.is_end(chunks.len()) {
                break;
            }
        }

        tokens
    }
}
