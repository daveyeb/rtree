use strum_macros::EnumString;

#[derive(Debug, PartialEq, EnumString, Clone)]
pub enum FileKind {
    #[strum(serialize = "java")]
    Java, 
    #[strum(serialize = "js", serialize = "ts")]
    JavaScript, 
    #[strum(serialize = "py")]
    Python, 
    #[strum(serialize = "rs")]
    Rust, 
    #[strum(serialize = "cpp")]
    CPlusPlus, 
    #[strum(serialize = "c")]
    C, 
    Unknown
}