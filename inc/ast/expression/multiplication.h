#ifndef CODECRAFTERS_INTERPRETER_MULTIPLICATION_H
#define CODECRAFTERS_INTERPRETER_MULTIPLICATION_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct Multiplication : Node {
  Multiplication(const lexer::Token &token, std::shared_ptr<Expression> left,
                 std::shared_ptr<Expression> right)
      : Node(token), left(std::move(left)), right(std::move(right)) {}

  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;
};
} // namespace lox::ast::expr

#endif
