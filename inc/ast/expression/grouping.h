#ifndef CODECRAFTERS_INTERPRETER_GROUPING_H
#define CODECRAFTERS_INTERPRETER_GROUPING_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct Grouping : Node {
  Grouping(const lexer::Token &token, std::shared_ptr<Expression> expression)
      : Node(token), expression(std::move(expression)) {}
  std::shared_ptr<Expression> expression;
};
} // namespace lox::ast::expr

#endif
