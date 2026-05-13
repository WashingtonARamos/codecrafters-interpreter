#ifndef CODECRAFTERS_INTERPRETER_NUMBER_H
#define CODECRAFTERS_INTERPRETER_NUMBER_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct Number : Node {
  Number(const lexer::Token &token)
      : Node(token), value(std::stod(token.value)) {}

  double value;
};
} // namespace lox::ast::expr

#endif
