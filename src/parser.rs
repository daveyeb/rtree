pub mod parser {
    use crate::Scanner;
    use crate::Token;
    use std::collections::HashSet;

    pub struct Parser {
        index: u128, // check if out of bounds
    }

    impl Scanner<HashSet<String>, Token> for Parser {
        fn current(&self, chunks: &Vec<Token>) -> Token {
            1
        }

        fn next(&self, chunks: &Vec<Token>) -> Token {
            1
        }

        fn scan(&self, chunks: &Vec<Token>) -> HashSet<String> {
            HashSet::new()
        }
    }
}
