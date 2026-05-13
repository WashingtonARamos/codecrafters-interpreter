#ifndef CODECRAFTERS_INTERPRETER_EQUALITY_H
#define CODECRAFTERS_INTERPRETER_EQUALITY_H
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/expr.h"
#include <memory>

namespace lox::ast::expr {
struct Equality : Node {
  Equality(const lexer::Token &token, std::shared_ptr<Expression> left,
           std::shared_ptr<Expression> right)
      : Node(token), left(std::move(left)), right(std::move(right)) {}

  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;
};
}

#endif
