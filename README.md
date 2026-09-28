# C Lexical Analyzer

A modular lexical analyzer (scanner) written in C. It reads C source code character by character, groups it into lexemes, and categorizes keywords, identifiers, constants, operators, delimiters, strings, and preprocessor directives. It also reports common lexical errors.

## Project Structure

* **`lexer.h`**: Core definitions, `Token` struct, enumerations, and function prototypes.
* **`main.c`**: The entry point that handles file I/O and coordinates the lexer loop.
* **`lexer.c`**: The core state machine implementing `getNextToken()`.
* **`token.c`**: Keyword dictionary, token creation, and lifecycle management.
* **`validator.c`**: Checks for illegal characters, malformed numbers, unterminated literals/comments, and mismatched brackets.
* **`report.c`**: Centralized terminal output formatting for valid tokens and error messages.
* **`sample.c`**: A test file containing valid C code mixed with intentional lexical errors.
* **`sample2.c`**: A clean, error-free C file for testing standard execution.

## How to Build

Ensure you have a C compiler (like GCC) installed, then compile all the `.c` modules together:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c lexer.c token.c validator.c report.c -o lexical_analyzer
```

Run it with a C source file:

```bash
./lexical_analyzer sample.c
```

Comments are skipped without using `strtok()`, so punctuation and token boundaries are preserved. The process exits with a non-zero status when lexical errors are found.
In WSL, go to the project folder through `/mnt/c/...`, then compile and run:

```bash
cd "/mnt/c/Users/mayan/Downloads/C PORTFOLIO/Lexical-Analyzer"
```

Compile:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c lexer.c token.c validator.c report.c -o lexical_analyzer
```

Run:

```bash
./lexical_analyzer sample2.c
```

Or run the other sample:

```bash
./lexical_analyzer sample.c
```

If `gcc` is not installed in WSL, install it with:

```bash
sudo apt update
sudo apt install build-essential
```