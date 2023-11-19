#pragma once

#include <string>

namespace Nebrix {
    class Tokens {
    public:
        enum Kind {
            // Single-character Tokens!
            LEFT_PAREN,    // (
            RIGHT_PAREN,   // )
            LEFT_BRACE,    // {
            RIGHT_BRACE,   // }
            LEFT_BRACKET,  // [
            RIGHT_BRACKET, // ]
            COMMA,         // ,
            DOT,           // .
            MINUS,         // -
            PLUS,          // +
            SEMICOLON,     // ;
            SLASH,         // /
            STAR,          // *
            HASHTAG,       // #
            COLON,         // :
            MODULO,        // %
            DOLLAR,        // $
            POWER,         // **
            TILDE,         // ~
            AT,            // @

            // One or two character tokens!
            BANG,          // !
            BANG_EQUAL,    // !=
            EQUAL,         // =
            GREATER,       // >
            GREATER_EQUAL, // >=
            LESS,          // <
            LESS_EQUAL,    // <=
            EXTENDS,       // extends
            INCREMENT,     // ++
            DECREMENT,     // --
            ARROW_L,       // <-
            ARROW_R,       // ->
            BIT_AND,       // &
            BIT_OR,        // |
            AND,           // &&
            OR,            // ||

            // Literals!
            IDENTIFIER,
            STRING,
            NUMBER,
            FLOAT,
            INAPPEND,

            // Keywords!
            LET, _CONST, IF, ELSE,
            FOR, BREAK,
            SWITCH, CASE, DEFAULT,
            IMPORT,

            // Types
            STRING_TYPE,
            CHAR_TYPE,
            INT_TYPE,
            FLOAT_TYPE,
            BOOL_TYPE,
            VOID_TYPE,
            ANY_TYPE,

            EOF_TOKEN,
            ERROR_TOKEN,
        };

        struct Token {
            const char* start;
            int length;
            Kind kind;
            int line;
            int pos;
        };

        const char* get_source_line_start(int line);
        void init_tokenization(const char* source);
        Token scan_token();
    };

    inline Tokens tokens;
}
