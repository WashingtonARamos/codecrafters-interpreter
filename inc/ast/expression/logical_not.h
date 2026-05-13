#ifndef CODECRAFTERS_INTERPRETER_LOGICAL_NOT_H
#define CODECRAFTERS_INTERPRETER_LOGICAL_NOT_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct LogicalNot : Node {
  LogicalNot(const lexer::Token &token, std::shared_ptr<Expression> right)
      : Node(token), right(std::move(right)) {}

  std::shared_ptr<Expression> right;
};
} // namespace lox::ast::expr

#endif
