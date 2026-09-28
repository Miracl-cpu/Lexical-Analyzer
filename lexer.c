#include "lexer.h"
#include <ctype.h>
#include <string.h>

static FILE *source = NULL;
static int line_number = 1;

static void append(char *buffer, size_t *length, int c) {
    if (*length + 1 < MAX_LEXEME_LENGTH) buffer[(*length)++] = (char)c;
}
static Token *make(TokenType type, char *buffer, size_t length, int line) {
    buffer[length] = '\0';
    return createToken(type, buffer, line);
}

void initLexer(FILE *source_file) { source = source_file; line_number = 1; }
void closeLexer(void) { source = NULL; }

Token *getNextToken(void) {
    int c;
    char buffer[MAX_LEXEME_LENGTH];
    size_t length = 0;

    if (!source) return createToken(TOKEN_EOF, "EOF", line_number);

    for (;;) {
        c = fgetc(source);
        if (c == EOF) return createToken(TOKEN_EOF, "EOF", line_number);
        if (isspace((unsigned char)c)) {
            if (c == '\n') ++line_number;
            continue;
        }
        if (c == '/') {
            int next = fgetc(source);
            if (next == '/') {
                while ((c = fgetc(source)) != EOF && c != '\n') {}
                if (c == '\n') ++line_number;
                continue;
            }
            if (next == '*') {
                int previous = 0;
                while ((c = fgetc(source)) != EOF) {
                    if (c == '\n') ++line_number;
                    if (previous == '*' && c == '/') break;
                    previous = c;
                }
                if (c == EOF)
                    return createToken(TOKEN_UNKNOWN, "unterminated comment", line_number);
                continue;
            }
            if (next != EOF) ungetc(next, source);
        }
        break;
    }

    int token_line = line_number;
    if (c == '#') {
        append(buffer, &length, c);
        while ((c = fgetc(source)) != EOF && c != '\n') append(buffer, &length, c);
        if (c == '\n') ungetc(c, source);
        return make(TOKEN_PREPROCESSOR, buffer, length, token_line);
    }

    if (isalpha((unsigned char)c) || c == '_') {
        append(buffer, &length, c);
        while ((c = fgetc(source)) != EOF &&
               (isalnum((unsigned char)c) || c == '_')) append(buffer, &length, c);
        if (c != EOF) ungetc(c, source);
        buffer[length] = '\0';
        return createToken(isKeyword(buffer) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER,
                           buffer, token_line);
    }

    if (isdigit((unsigned char)c)) {
        bool decimal = false;
        do {
            if (c == '.') decimal = true;
            append(buffer, &length, c);
            c = fgetc(source);
        } while (isdigit((unsigned char)c) || c == '.');
        if (c != EOF) ungetc(c, source);
        return make(decimal ? TOKEN_FLOAT : TOKEN_INTEGER, buffer, length, token_line);
    }
    if (c == '.') {
        int next = fgetc(source);
        if (isdigit((unsigned char)next)) {
            append(buffer, &length, c);
            c = next;
            do {
                append(buffer, &length, c);
                c = fgetc(source);
            } while (isdigit((unsigned char)c) || c == '.');
            if (c != EOF) ungetc(c, source);
            return make(TOKEN_FLOAT, buffer, length, token_line);
        }
        if (next != EOF) ungetc(next, source);
    }

    if (c == '"' || c == '\'') {
        int quote = c;
        bool closed = false, escaped = false;
        append(buffer, &length, c);
        while ((c = fgetc(source)) != EOF) {
            append(buffer, &length, c);
            if (c == '\n') ++line_number;
            if (c == quote && !escaped) { closed = true; break; }
            if (c == '\\' && !escaped) escaped = true;
            else escaped = false;
        }
        if (!closed) return make(TOKEN_UNKNOWN, buffer, length, token_line);
        return make(quote == '"' ? TOKEN_STRING : TOKEN_CHARACTER,
                    buffer, length, token_line);
    }

    if (strchr("+-*/%=<>!&|^~?", c)) {
        append(buffer, &length, c);
        int next = fgetc(source);
        bool two = (next == '=' && strchr("=<>!+-*/%&|^", c)) ||
                   (next == c && strchr("+-&|", c)) ||
                   (c == '-' && next == '>');
        if (two) append(buffer, &length, next);
        else if (next != EOF) ungetc(next, source);
        return make(TOKEN_OPERATOR, buffer, length, token_line);
    }

    if (strchr(";,(){}[]:", c)) {
        append(buffer, &length, c);
        return make(TOKEN_DELIMITER, buffer, length, token_line);
    }

    append(buffer, &length, c);
    return make(TOKEN_UNKNOWN, buffer, length, token_line);
}

