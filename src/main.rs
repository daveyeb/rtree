
mod token;
mod lexer; 
mod util;
mod scanner;
mod rules;

use lexer::Lexer;
use token::Token; 
use scanner::Scanner;
use rules::Rules;


fn main() {
    let chunks = &"sva".to_string().into_bytes();
    let mut lexer= Lexer::new();
    lexer.next(chunks);
    lexer.peek(chunks);
    lexer.scan(chunks);
    
    
}
