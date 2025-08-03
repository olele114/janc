use std::io::{BufRead, BufReader, Read};
use crate::token::Token;

/// Lexical analyzer that converts input characters into tokens
/// 
/// Maintains state including:
/// - Input reader with buffering
/// - Putback character for lookahead
/// - Current line number
pub struct Lexer<R: Read> {
    reader: BufReader<R>,
    putback: Option<char>,
    line: u32,
}

impl <R: Read> Lexer<R> {
    /// Creates a new lexer instance from a readable source
    /// 
    /// # Arguments
    /// * `reader` - Input source implementing the Read trait
    pub fn new(reader: R) -> Self {
        Lexer {
            reader: BufReader::new(reader),
            putback: None,
            line: 1,
        }
    }

    /// Fetches the next character from input
    /// 
    /// Handles putback character priority and tracks newlines
    /// Returns None when end of input is reached
    fn next_char(&mut self) -> Option<char> {
        // Use putback character if available
        if let Some(c) = self.putback.take() {
            return Some(c);
        }

        let mut buf = [0u8; 1];
        match self.reader.read_exact(&mut buf) {
            Ok(_) => {
                let c = buf[0] as char;
                // Increment line counter on newline
                if c == '\n' {
                    self.line += 1;
                }
                Some(c)
            }
            Err(_) => None,
        }
    }

    /// Returns a character to the input stream
    /// 
    /// # Arguments
    /// * `c` - Character to put back
    fn put_back(&mut self, c: char) {
        self.putback = Some(c);
    }

    /// Skips whitespace characters and returns the first non-whitespace
    /// 
    /// Consumes all whitespace characters (space, tab, newline, etc.)
    /// Returns None when end of input is reached
    fn skip_whitespace(&mut self) -> Option<char> {
        while let Some(c) = self.next_char() {
            if !c.is_whitespace() {
                return Some(c);
            }
        }
        None
    }

    /// Scans an integer literal from input
    /// 
    /// # Arguments
    /// * `first_char` - First digit character already consumed
    /// 
    /// # Returns
    /// Parsed integer value
    fn scan_int(&mut self, first_char: char) -> i32 {
        let mut val = first_char.to_digit(10).unwrap() as i32;

        // Consume consecutive digits
        while let Some(c) = self.next_char() {
            if let Some(digit) = c.to_digit(10) {
                val = val * 10 + digit as i32;
            } else {
                // Non-digit character, put back for next token
                self.put_back(c);
                break;
            }
        }
        val
    }

    /// Scans and returns the next token
    /// 
    /// # Returns
    /// - `Some(Ok(token))` when valid token found
    /// - `Some(Err(message))` when invalid character encountered
    /// - `None` when end of input reached
    /// 
    /// # Process
    /// 1. Skips leading whitespace
    /// 2. Matches character to token type
    /// 3. Handles integer literal parsing
    /// 4. Reports syntax errors with line numbers
    pub fn scan(&mut self) -> Option<Result<Token, String>> {
        // Get next non-whitespace character
        let c = match self.skip_whitespace() {
            Some(c) => c,
            None => return None,
        };

        let token = match c {
            '+' => Ok(Token::Plus),
            '-' => Ok(Token::Minus),
            '*' => Ok(Token::Star),
            '/' => Ok(Token::Slash),

            // Integer literal processing
            _ if c.is_ascii_digit() => Ok(Token::IntLit(self.scan_int(c))),
            
            // Syntax error handling
            _ => Err(format!("Unrecognised character '{}' on line {}", c, self.pine)),
        };

        Some(token)
    }
}
