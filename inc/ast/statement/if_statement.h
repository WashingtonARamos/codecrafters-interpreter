#ifndef CODECRAFTERS_INTERPRETER_IF_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_IF_STATEMENT_H
#include "../../lexer/token.h"
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct IfStatement : Node {
  IfStatement(const lexer::Token &token,
              std::shared_ptr<expr::Expression> condition,
              std::shared_ptr<Statement> if_body,
              std::shared_ptr<Statement> else_statements = nullptr)
      : Node(token), condition(std::move(condition)),
        if_stmt(std::move(if_body)), else_stmt(std::move(else_statements)) {}

  std::shared_ptr<expr::Expression> condition;
  std::shared_ptr<Statement> if_stmt;
  std::shared_ptr<Statement> else_stmt;
};
} // namespace lox::ast::stmt

#endif
