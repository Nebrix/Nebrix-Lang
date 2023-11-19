#pragma once

#include <unordered_map>
#include <string>

#include "tokens.hpp"

using namespace Nebrix;

struct Scanner {
    const char *current;
    const char *source;
    const char *start;
    int column;
    int line;
};
inline Scanner scanner;

static bool is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}
static bool is_digit(char c) { return c >= '0' && c <= '9'; }
static bool is_at_end() { return *scanner.current == '\0'; }

static char advance()
{
    scanner.current++;
    scanner.column++;
    return scanner.current[-1];
}

static char peek_next() { return scanner.current[1]; }
static char peek() { return *scanner.current; }

static bool match(char expected)
{
    if (is_at_end())
        return false;
    if (*scanner.current != expected)
        return false;

    scanner.current++;
    scanner.column++;
    return true;
}

static Tokens::Token make_token(Tokens::Kind kind)
{
    Tokens::Token token;
    token.kind = kind;
    token.line = scanner.line;
    token.start = scanner.start;
    token.pos = scanner.column;
    token.length = static_cast<int>(scanner.current - scanner.start);
    return token;
}

static Tokens::Token error_token(std::string message)
{
    Tokens::Token token;
    token.kind = Tokens::Kind::ERROR_TOKEN;
    token.start = message.c_str();
    token.length = message.length();
    token.line = scanner.line;
    return token;
}

static void skip_whitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            scanner.line++;
            scanner.column = 0;
            advance();
            break;
        case '/':
            if (peek_next() == '/')
                while (peek() != '\n' && !is_at_end())
                    advance();
            else
                return;
            break;
        default:
            return;
        }
    }
}

static Tokens::Token _string()
{
    while ((peek() != '"') && !is_at_end())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }
    if (is_at_end())
        error_token("Unterminated string.");
    advance(); // advance past the closing '"'
    return make_token(Tokens::Kind::STRING);
}

struct Keyword
{
    std::string keyword;
    Tokens::Kind kind;
};

static Tokens::Kind perfect_hash_lookup(std::string keyword)
{
    static const std::unordered_map<std::string, Tokens::Kind> keyword_hash{
        {"let",     Tokens::Kind::LET},
        {"const",   Tokens::Kind::_CONST},
        {"if",      Tokens::Kind::IF},
        {"else",    Tokens::Kind::ELSE},
        {"for",     Tokens::Kind::FOR},
        {"break",   Tokens::Kind::BREAK},
        {"switch",  Tokens::Kind::SWITCH},
        {"case",    Tokens::Kind::CASE},
        {"default", Tokens::Kind::DEFAULT},
        {"add",     Tokens::Kind::IMPORT},

        // Types
        {"string",  Tokens::Kind::STRING_TYPE},
        {"char",    Tokens::Kind::CHAR_TYPE},
        {"int",     Tokens::Kind::INT_TYPE},
        {"float",   Tokens::Kind::FLOAT_TYPE},
        {"bool",    Tokens::Kind::BOOL_TYPE},
        {"void",    Tokens::Kind::VOID_TYPE},
        {"any",     Tokens::Kind::ANY_TYPE},
    };

    auto it = keyword_hash.find(keyword);
    if (it != keyword_hash.end())
        return it->second;
    return Tokens::Kind::IDENTIFIER;
}

static Tokens::Kind identifier_type()
{
    std::string keyword(scanner.start, scanner.current);
    return perfect_hash_lookup(keyword.c_str());
}

static Tokens::Token identifier()
{
    while (is_alpha(peek()) || is_digit(peek()))
        advance();
    return make_token(identifier_type());
}

static Tokens::Token number()
{
    while (is_digit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && is_digit(peek_next()))
    {
        advance(); // Consume the "."

        while (is_digit(peek()))
            advance();
        
        return make_token(Tokens::Kind::FLOAT);
    }
    // print out the number
    return make_token(Tokens::Kind::NUMBER);
}