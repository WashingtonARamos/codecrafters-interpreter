#ifndef CODECRAFTERS_INTERPRETER_PRINT_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_PRINT_STATEMENT_H
#include "../../lexer/token.h"
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct PrintStatement : Node {
  PrintStatement(const lexer::Token &token,
                 std::shared_ptr<expr::Expression> expression)
      : Node(token), expression(std::move(expression)) {}
  std::shared_ptr<expr::Expression> expression;
};
} // namespace lox::ast::stmt

#endif
