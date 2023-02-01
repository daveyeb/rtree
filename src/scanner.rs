pub trait Scanner<T, U> {
    fn current(&self, chunks: &Vec<U>) -> U;
    fn peek(&self, chunks: &Vec<U>) -> Option<U>;
    fn next(&mut self, chunks: &Vec<U>) -> U;
    fn scan(&mut self, chunks: &Vec<U>) -> T;
}
