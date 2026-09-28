#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_LEXEME_LENGTH 256

typedef enum {
    TOKEN_PREPROCESSOR, TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR,
    TOKEN_INTEGER, TOKEN_FLOAT, TOKEN_STRING, TOKEN_CHARACTER, TOKEN_DELIMITER,
    TOKEN_UNKNOWN, TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;
    int line_number;
} Token;

Token *createToken(TokenType type, const char *lexeme, int line_number);
void freeToken(Token *token);
bool isKeyword(const char *str);
const char *getTokenTypeName(TokenType type);

void initLexer(FILE *source_file);
Token *getNextToken(void);
void closeLexer(void);

void initValidator(void);
void validateToken(const Token *token);
void reportValidationErrors(void);
int getValidationErrorCount(void);

void printToken(const Token *token);
void printLexicalError(const char *message, int line_number);
void printFinalSummary(int total_tokens, int total_errors);

#endif

