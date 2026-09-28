#include "lexer.h"
#include <stdio.h>
#include <string.h>

static char bracket_stack[256];
static int bracket_top;
static int errors;

void initValidator(void) { bracket_top = 0; errors = 0; }

static bool matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

void validateToken(const Token *token) {
    if (!token) return;
    if (token->type == TOKEN_UNKNOWN) {
        printLexicalError("Unrecognized character or unterminated literal/comment",
                          token->line_number);
        ++errors;
        return;
    }
    if (token->type == TOKEN_DELIMITER) {
        char c = token->lexeme[0];
        if (c == '(' || c == '[' || c == '{') {
            if (bracket_top < (int)sizeof bracket_stack)
                bracket_stack[bracket_top++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (bracket_top == 0 || !matches(bracket_stack[bracket_top - 1], c)) {
                printLexicalError("Mismatched closing bracket", token->line_number);
                ++errors;
            } else --bracket_top;
        }
    }
    if (token->type == TOKEN_FLOAT &&
        strchr(token->lexeme, '.') != strrchr(token->lexeme, '.')) {
        printLexicalError("Malformed floating-point constant", token->line_number);
        ++errors;
    }
}

void reportValidationErrors(void) {
    if (bracket_top > 0) {
        fprintf(stderr, "[LEXICAL ERROR] %d unmatched opening bracket(s)\n", bracket_top);
        errors += bracket_top;
    }
}

int getValidationErrorCount(void) { return errors; }

