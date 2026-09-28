#include "lexer.h"
#include <stdio.h>

void printToken(const Token *token) {
    if (!token) return;
    printf("%-5d | %-25s | %s\n", token->line_number,
           getTokenTypeName(token->type), token->lexeme);
}

void printLexicalError(const char *message, int line_number) {
    fprintf(stderr, "[LEXICAL ERROR] Line %-3d: %s\n", line_number, message);
}

void printFinalSummary(int total_tokens, int total_errors) {
    printf("------------------------------------------------------\n");
    printf("Lexical analysis complete: %d token(s), %d error(s).\n",
           total_tokens, total_errors);
}

