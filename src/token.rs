use std::str::FromStr;
use strum_macros::EnumString;

#[derive(Debug, EnumString, Clone)]
pub enum TokenKind {
    Unknown,
    #[strum(serialize = "from")]
    From,
    #[strum(serialize = "import")]
    Import,
    #[strum(serialize = "use")]
    Use,
    #[strum(serialize = "load")]
    Load,
    #[strum(serialize = "require")]
    Require,
    #[strum(serialize = "include")]
    Include,
    #[strum(serialize = "(")]
    OpenParen,
    #[strum(serialize = ")")]
    CloseParen,
    #[strum(serialize = "#")]
    Pound,
    #[strum(serialize = "*")]
    Asterik,
    #[strum(serialize = ",")]
    Comma,
    #[strum(serialize = ".")]
    Period,
    #[strum(serialize = "/")]
    ForwardSlash,
    #[strum(serialize = ";")]
    SemiColon,
    #[strum(serialize = "<")]
    LessThan,
    #[strum(serialize = ">")]
    GreaterThan,
    #[strum(serialize = "{")]
    OpenCurly,
    #[strum(serialize = "}")]
    CloseCurly,
    Literal,
}

#[derive(Debug, Clone)]
pub struct Token {
    kind: TokenKind,
    lexeme: String,
    raw: String,
}

impl Token {
    pub fn new(string: &str) -> Token {
        let token_kind;
        match TokenKind::from_str(&string) {
            Ok(x) => token_kind = x,
            Err(_) => token_kind = TokenKind::Unknown,
        }

        Token {
            kind: token_kind,
            lexeme: string.to_string(),
            raw: format!("\"{}\"", string),
        }
    }

    pub fn as_literal(string: &str) -> Token {
        Token {
            kind: TokenKind::Literal,
            lexeme: string.to_string(),
            raw: format!("\"{}\"", string),
        }
    }

    pub fn kind(&self) -> TokenKind {
        self.kind.clone()
    }

    pub fn lexeme(&self) -> String {
      self.lexeme.clone()
  }
}

impl Default for Token {
    fn default() -> Self {
        Token {
            kind: TokenKind::Unknown,
            lexeme: "".to_string(),
            raw: "".to_string(),
        }
    }
}
