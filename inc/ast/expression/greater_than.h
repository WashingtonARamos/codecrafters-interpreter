#ifndef CODECRAFTERS_INTERPRETER_GREATER_THAN_H
#define CODECRAFTERS_INTERPRETER_GREATER_THAN_H
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/expr.h"
#include <memory>

namespace lox::ast::expr {
struct GreaterThan : Node {
  GreaterThan(const lexer::Token &token, std::shared_ptr<Expression> left,
              std::shared_ptr<Expression> right)
      : Node(token), left(std::move(left)), right(std::move(right)) {}

  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;
};
} // namespace lox::ast::expr

#endif
