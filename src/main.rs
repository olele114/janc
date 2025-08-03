mod lexer;
mod token;

use std::fs::File;
use std::env;
use std::process;
use lexer::Lexer;
use token::Token;

/// Prints usage information and exits with error code
/// 
/// # Arguments
/// * `prog` - Program name from command line
fn usage(prog: &str) {
    eprintln!("Usage: {} infile", prog);
    process::exit(1);
}

/// Main application workflow:
/// 1. Parses command line arguments
/// 2. Initializes lexer with input file
/// 3. Scans tokens until end of file
/// 4. Prints tokens or exits on error
/// 
/// # Exit Codes
/// - 0: Successful execution
/// - 1: Command line or file I/O error
/// - 2: Lexical analysis error
fn main() {
    let args: Vec<String> = env::args().collect();

    // Validate command line Arguments
    if args.len() != 2 {
        usage(&args[0]);
    }

    // Open input file
    let file = match File::open(&args[1]) {
        Ok(f) => f,
        Err(e) => {
            eprintln!("Unable to open {}: {}", args[1], e);
            process::exit(1);
        }
    };

    // Initialize lexer
    let mut lexer = Lexer::new(file);

    // Token scanning loop
    while let Some(result) = lexer.scan() {
        match result {
            Ok(token) => {
                // Special handling for integer literals
                match token {
                    Token::IntLit(n) => println!("Token intlit, value {}", n),
                    _ => println!("Token {}", token.to_string()),
                }
            }
            Err(e) => {
                // Lexical error reporting
                eprintln!("{}", e);
                process::exit(2);
            }
        }
    }
}
