#ifndef CODECRAFTERS_INTERPRETER_TOKEN_H
#define CODECRAFTERS_INTERPRETER_TOKEN_H
#include <string>

namespace lox::lexer {
  enum class TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    IDENTIFIER,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    ASSIGN,
    EQUALS,
    BANG,
    UNEQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_OR_EQUAL_TO,
    GREATER_OR_EQUAL_TO,
    STRING,
    NUMBER,
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,
    NEW_LINE,
    UNEXPECTED_TOKEN,
    UNTERMINATED_STRING,
    END_OF_FILE
  };

  struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;
  };

  std::string to_string(const Token& token);
  inline bool is_eof(const Token& token) { return token.type == TokenType::END_OF_FILE; }
  inline bool is_bad_token(const Token& token) {
    return token.type == TokenType::UNEXPECTED_TOKEN ||
           token.type == TokenType::UNTERMINATED_STRING;
  }
}

#endif
