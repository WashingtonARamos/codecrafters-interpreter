#ifndef CODECRAFTERS_INTERPRETER_ASSIGNMENT_H
#define CODECRAFTERS_INTERPRETER_ASSIGNMENT_H
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/expr.h"
#include <memory>

namespace lox::ast::expr {
struct Assignment : Node {
  Assignment(const lexer::Token &token, std::shared_ptr<Expression> name,
             std::shared_ptr<Expression> value)
      : Node(token), target(std::move(name)), value(std::move(value)) {}

  std::shared_ptr<Expression> target;
  std::shared_ptr<Expression> value;
};
} // namespace lox::ast::expr

#endif
