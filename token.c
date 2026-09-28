#include "lexer.h"
#include <stdlib.h>
#include <string.h>

static const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do","double","else",
    "enum","extern","float","for","goto","if","inline","int","long","register",
    "restrict","return","short","signed","sizeof","static","struct","switch",
    "typedef","union","unsigned","void","volatile","while","_Bool","_Complex","_Imaginary"
};

bool isKeyword(const char *str) {
    size_t count = sizeof keywords / sizeof keywords[0];
    for (size_t i = 0; i < count; ++i)
        if (strcmp(str, keywords[i]) == 0) return true;
    return false;
}

Token *createToken(TokenType type, const char *lexeme, int line_number) {
    Token *token = malloc(sizeof *token);
    if (!token) return NULL;
    token->lexeme = malloc(strlen(lexeme) + 1);
    if (!token->lexeme) { free(token); return NULL; }
    strcpy(token->lexeme, lexeme);
    token->type = type;
    token->line_number = line_number;
    return token;
}

void freeToken(Token *token) {
    if (token) { free(token->lexeme); free(token); }
}

const char *getTokenTypeName(TokenType type) {
    switch (type) {
        case TOKEN_PREPROCESSOR: return "Preprocessor Directive";
        case TOKEN_KEYWORD: return "Keyword";
        case TOKEN_IDENTIFIER: return "Identifier";
        case TOKEN_OPERATOR: return "Operator";
        case TOKEN_INTEGER: return "Integer Constant";
        case TOKEN_FLOAT: return "Float Constant";
        case TOKEN_STRING: return "String Literal";
        case TOKEN_CHARACTER: return "Character Constant";
        case TOKEN_DELIMITER: return "Delimiter";
        case TOKEN_UNKNOWN: return "Unknown Character";
        case TOKEN_EOF: return "End of File";
    }
    return "Undefined Type";
}

