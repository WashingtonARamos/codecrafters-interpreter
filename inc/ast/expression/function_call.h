#ifndef CODECRAFTERS_INTERPRETER_FUNCTION_CALL_H
#define CODECRAFTERS_INTERPRETER_FUNCTION_CALL_H
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/expr.h"

#include <memory>
#include <utility>
#include <vector>

namespace lox::ast::expr {
struct FunctionCall : Node {
  FunctionCall(const lexer::Token &token, std::shared_ptr<Expression> callee,
               std::vector<std::shared_ptr<Expression>> arguments)
      : Node(token), callee(std::move(callee)),
        arguments(std::move(arguments)) {}

  std::shared_ptr<Expression> callee;
  std::vector<std::shared_ptr<Expression>> arguments;
};
} // namespace lox::ast::expr

#endif
