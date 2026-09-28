#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file.c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *source_file = fopen(argv[1], "r");
    if (!source_file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("Analyzing file: %s\n", argv[1]);
    printf("------------------------------------------------------\n");
    printf("%-5s | %-25s | %s\n", "Line", "Token Type", "Lexeme");
    printf("------------------------------------------------------\n");

    initLexer(source_file);
    initValidator();
    int total_tokens = 0;
    Token *current_token;

    do {
        current_token = getNextToken();
        if (!current_token) {
            fprintf(stderr, "Unable to allocate memory for a token.\n");
            closeLexer();
            fclose(source_file);
            return EXIT_FAILURE;
        }
        if (current_token->type != TOKEN_EOF) {
            printToken(current_token);
            validateToken(current_token);
            ++total_tokens;
        }
        bool end = current_token->type == TOKEN_EOF;
        freeToken(current_token);
        if (end) break;
    } while (true);

    reportValidationErrors();
    printFinalSummary(total_tokens, getValidationErrorCount());
    closeLexer();
    fclose(source_file);
    return getValidationErrorCount() == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

