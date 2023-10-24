use std::str::FromStr;
use strum_macros::EnumString;

#[derive(Debug, Clone, EnumString)]
pub enum Token {
    Unknown,
    #[strum(serialize = "(")]
    OpenParen(u8),
    #[strum(serialize = ")")]
    CloseParen(u8),
    #[strum(serialize = "#")]
    Pound(u8),
    #[strum(serialize = "*")]
    Asterik(u8),
    #[strum(serialize = ",")]
    Comma(u8),
    #[strum(serialize = ".")]
    Period(u8),
    #[strum(serialize = "/")]
    ForwardSlash(u8),
    #[strum(serialize = ";")]
    SemiColon(u8),
    #[strum(serialize = "<")]
    LessThan(u8),
    #[strum(serialize = ">")]
    GreaterThan(u8),
    #[strum(serialize = "{")]
    OpenCurly(u8),
    #[strum(serialize = "}")]
    CloseCurly(u8),
    #[strum(serialize = "from")]
    From(String),
    #[strum(serialize = "import")]
    Import(String),
    #[strum(serialize = "use")]
    Use(String),
    #[strum(serialize = "load")]
    Load(String),
    #[strum(serialize = "require")]
    Require(String),
    #[strum(serialize = "include")]
    Include(String),
    #[strum(disabled)]
    Literal(String),
    Identifier(String)
}

impl Token {
    pub fn new(some: &str) -> Self {
        let token = match Token::from_str(some) {
            Ok(t) => match t {
                Token::OpenParen(_) => Token::OpenParen(some.chars().next().unwrap() as u8),
                Token::CloseParen(_) => Token::CloseParen(some.chars().next().unwrap() as u8),
                Token::Pound(_) => Token::Pound(some.chars().next().unwrap() as u8),
                Token::Asterik(_) => Token::Asterik(some.chars().next().unwrap() as u8),
                Token::Comma(_) => Token::Comma(some.chars().next().unwrap() as u8),
                Token::Period(_) => Token::Period(some.chars().next().unwrap() as u8),
                Token::ForwardSlash(_) => Token::ForwardSlash(some.chars().next().unwrap() as u8),
                Token::SemiColon(_) => Token::SemiColon(some.chars().next().unwrap() as u8),
                Token::LessThan(_) => Token::LessThan(some.chars().next().unwrap() as u8),
                Token::GreaterThan(_) => Token::GreaterThan(some.chars().next().unwrap() as u8),
                Token::OpenCurly(_) => Token::OpenCurly(some.chars().next().unwrap() as u8),
                Token::CloseCurly(_) => Token::CloseCurly(some.chars().next().unwrap() as u8),
                Token::From(_) => Token::From(some.to_string()),
                Token::Import(_) => Token::Import(some.to_string()),
                Token::Use(_) => Token::Use(some.to_string()),
                Token::Load(_) => Token::Load(some.to_string()),
                Token::Require(_) => Token::Require(some.to_string()),
                Token::Include(_) => Token::Include(some.to_string()),
                // manually will instantiate literal
                _ => Token::Unknown
            },
            Err(_) => {
              // println!("some outside {}", some);
              Token::Identifier(some.to_string())
            },
        };
        token
    }

    pub fn lexeme(&self) -> Option<String> {
        match self {
            Token::From(x) => Some(x.to_string()),
            Token::Import(x) => Some(x.to_string()),
            Token::Use(x) => Some(x.to_string()),
            Token::Load(x) => Some(x.to_string()),
            Token::Require(x) => Some(x.to_string()),
            Token::Include(x) => Some(x.to_string()),
            Token::Literal(x) => Some(x.to_string()),
            Token::Identifier(x) => Some(x.to_string()),
            _ => None,
        }
    }

}

impl Default for Token {
    // tbd
    fn default() -> Self {
        Token::Unknown
    }
}
