#ifndef CODECRAFTERS_INTERPRETER_UNARY_MINUS_H
#define CODECRAFTERS_INTERPRETER_UNARY_MINUS_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct UnaryMinus : Node {
  UnaryMinus(const lexer::Token &token, std::shared_ptr<Expression> right)
      : Node(token), right(std::move(right)) {}

  std::shared_ptr<Expression> right;
};
} // namespace lox::ast::expr

#endif
