use std::collections::HashMap;

pub trait Parser<T, U> {
    fn current(&self, tokens: &Vec<U>) -> Option<U>;
    fn peek(&self, tokens: &Vec<U>) -> Option<U>;
    fn next(&mut self, tokens: &Vec<U>) -> Option<U>;
    fn parse(&mut self, deps: &mut HashMap<String, String>, file_tokens: (&T, &Vec<U>));
}
