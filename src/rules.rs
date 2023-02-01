pub mod Rules {
    use crate::{scanner::Scanner, Lexer, Token};

    pub fn identifier(lexer: &Lexer, chunks: &Vec<u8>) -> Option<Token> {
        let ch = lexer.current(chunks);

        // if(ch.is_ascii()) {
        //     return None;
        // }

        Some(Token {
            lexeme: "sdf".to_string(),
            raw: "\"sdf\"".to_string(),
        })
    }

    pub fn literal(lexer: &Lexer, chunks: &Vec<u8>) -> Option<Token>  {
        Some(Token {
            lexeme: "sdf".to_string(),
            raw: "\"sdf\"".to_string(),
        })
    }
    pub fn punctuation(lexer: &Lexer, chunks: &Vec<u8>) -> Option<Token>  {
        Some(Token {
            lexeme: "sdf".to_string(),
            raw: "\"sdf\"".to_string(),
        })
    }

    pub fn comment(lexer: &Lexer, chunks: &Vec<u8>) {

    }
    pub fn unknown(lexer: &Lexer, chunks: &Vec<u8>) {

    }

}
