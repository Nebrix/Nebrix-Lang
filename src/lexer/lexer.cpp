#include <string>
#include <unordered_map>

#include "../helper/errors/lexer_error.hpp"

#include "lexer.hpp"
#include "tokens.hpp"

using namespace Nebrix;

Tokens::Token Tokens::scan_token() {
  skip_whitespace();
  scanner.start = scanner.current;

  if (is_at_end())
    return make_token(Tokens::Kind::EOF_TOKEN);

  char c = advance();

  if (isdigit(c))
    return number();
  if (isalpha(c))
    return identifier();

  switch (c) {
  case ')':
    return make_token(Tokens::Kind::RIGHT_PAREN);
  case '(':
    return make_token(Tokens::Kind::LEFT_PAREN);
  case '{':
    return make_token(Tokens::Kind::LEFT_BRACE);
  case '}':
    return make_token(Tokens::Kind::RIGHT_BRACE);
  case '[':
    return make_token(Tokens::Kind::LEFT_BRACKET);
  case ']':
    return make_token(Tokens::Kind::RIGHT_BRACKET);
  case ';':
    return make_token(Tokens::Kind::SEMICOLON);
  case ',':
    return make_token(Tokens::Kind::COMMA);
  case '.':
    return make_token(Tokens::Kind::DOT);
  case '/':
    return make_token(Tokens::Kind::SLASH);
  case '%':
    return make_token(Tokens::Kind::MODULO);
  case '#':
    return make_token(Tokens::Kind::HASHTAG);
  case '~':
    return make_token(Tokens::Kind::TILDE);
  case '@':
    return make_token(Tokens::Kind::AT);
  case '=':
    return make_token(Tokens::Kind::EQUAL);
  case '+':
    return make_token(match('+') ? Tokens::Kind::INCREMENT : Tokens::Kind::PLUS);
  case ':':
    return make_token(Tokens::Kind::COLON);
  case '-': {
    if (match('>')) return make_token(Tokens::Kind::ARROW_R);
    else if (match('-')) return make_token(Tokens::Kind::DECREMENT);
    else return make_token(Tokens::Kind::MINUS);
  }
  case '&':
    return make_token(match('&') ? Tokens::Kind::AND : Tokens::Kind::BIT_AND);
  case '|':
    return make_token(match('|') ? Tokens::Kind::OR : Tokens::Kind::BIT_OR);
  case '*':
    return make_token(match('*') ? Tokens::Kind::POWER : Tokens::Kind::STAR);
  case '!':
    return make_token(match('=') ? Tokens::Kind::BANG_EQUAL : Tokens::Kind::BANG);
  case '>':
    return make_token(match('=') ? Tokens::Kind::GREATER_EQUAL : Tokens::Kind::GREATER);
  case '<': {
    if (match('=')) return make_token(Tokens::Kind::LESS_EQUAL);
    else if (match('-')) return make_token(Tokens::Kind::ARROW_L);
    else return make_token(Tokens::Kind::LESS);
  }
  case '"':
    return _string();
  }

  LexerError::error_lexer(&scanner, "Unexpected character: " + std::string(1, c));
  return make_token(Tokens::Kind::ERROR_TOKEN);
}