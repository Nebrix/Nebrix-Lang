#include <string>

#include "tokens.hpp"
#include "lexer.hpp"

using namespace Nebrix;

void Tokens::init_tokenization(const char* source) {
    scanner.current = source;
    scanner.source = source;
    scanner.start = source;
    scanner.column = 0;
    scanner.line = 1;
}

const char* Tokens::get_source_line_start(int line) {
    const char *current = scanner.source;
    int current_line = 1;

    while (current_line < line && *current != '\0')
    {
        if (*current == '\n')
            current_line++;
        current++;
    }

    // Include leading whitespace
    while (*current != '\n' && *current != '\0' && isspace(*current))
        current--;
    if (*current++ == '\n')
        current++;
    return current;
}