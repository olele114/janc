/// Defines all token types recognized by the lexer
#[derive(Debug, PartialEq)]
pub enum Token {
    /// Addition operator '+'
    Plus,
    /// Subtraction operator '-'
    Minus,
    /// Multiplication operator '*'
    Star,
    /// Division operator '/'
    Slash,
    /// Integer literal (e.g., 42)
    IntLit(i32),
}

impl Token {
    /// Returns a string representation of the token for display purposes
    /// 
    /// # Examples
    /// ```
    /// let token = Token::Plus;
    /// assert_eq!(token.to_string(), "+");
    /// 
    /// let token = Token::IntLit(42);
    /// assert_eq!(token.to_string(), "42");
    /// ```
    pub fn to_string(&self) -> String {
        match self {
            Token::Plus => "+".to_string(),
            Token::Minus => "-".to_string(),
            Token::Star => "*".to_string(),
            Token::Slash => "/".to_string(),
            Token::IntLit(n) => format!("{}", n),
        }
    }
}
