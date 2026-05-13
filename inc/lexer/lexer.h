#ifndef CODECRAFTERS_INTERPRETER_LEXER_H
#define CODECRAFTERS_INTERPRETER_LEXER_H
#include "token.h"
#include <string>
#include <string_view>

namespace lox::lexer {
class Lexer {
  std::string_view &sv;
  size_t pos_ = 0;
  size_t line_ = 1;
  size_t line_pos_ = 0;

  [[nodiscard]] Token MakeToken(TokenType type, const std::string &value) const;
  [[nodiscard]] Token SingleChar(TokenType type);

  char Advance();
  [[nodiscard]] char Peek() const;

public:
  explicit Lexer(std::string_view &string_view);
  [[nodiscard]] size_t line() const { return line_; }
  [[nodiscard]] size_t line_pos() const { return line_pos_; }
  Token NextToken();
  [[nodiscard]] Token PeekNext() const;
};
} // namespace lox::lexer

#endif
