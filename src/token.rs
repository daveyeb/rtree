use crate::tokenkind::TokenKind;

#[derive(Clone)]
pub struct Token {
    pub kind: TokenKind,
    pub lexeme: String,
    pub raw: String,
}

impl Token {
    pub fn new() -> Self {
        Token {
            kind: TokenKind::Unknown,
            lexeme: "".to_string(),
            raw: "".to_string(),
        }
    }
}
