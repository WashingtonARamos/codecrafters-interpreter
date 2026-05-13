#ifndef CODECRAFTERS_INTERPRETER_WHILE_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_WHILE_STATEMENT_H
#include "../../lexer/token.h"
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct While : Node {
  While(const lexer::Token &token,
        const std::shared_ptr<expr::Expression> &condition,
        const std::shared_ptr<Statement> &body)
      : Node(token), condition(condition), body(body) {}

  std::shared_ptr<expr::Expression> condition;
  std::shared_ptr<Statement> body;
};
} // namespace lox::ast::stmt

#endif