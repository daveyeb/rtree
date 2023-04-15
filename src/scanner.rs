pub trait Scanner<T, U, F> {
    fn current(&self, chunks: &Vec<U>) -> Option<U>;
    fn peek(&self, chunks: &Vec<U>) -> Option<U>;
    fn next(&mut self, chunks: &Vec<U>) -> Option<U>;
    fn scan(&mut self, file_chunks: (&F, &Vec<U>)) -> T;
}
