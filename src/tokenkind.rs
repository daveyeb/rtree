use strum_macros::EnumString;

#[derive(Debug, PartialEq, EnumString, Clone)]
pub enum TokenKind {
    Unknown, 
    #[strum(serialize = "from")]
    From ,
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