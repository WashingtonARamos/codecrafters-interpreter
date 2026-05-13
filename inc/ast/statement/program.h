#ifndef CODECRAFTERS_INTERPRETER_PROGRAM_H
#define CODECRAFTERS_INTERPRETER_PROGRAM_H
#include "../node.h"
#include "fwd/statement.h"

namespace lox::ast::stmt {
struct Program : Node {
  explicit Program(std::vector<std::shared_ptr<Statement>> statements)
      : Node(lexer::Token{lexer::TokenType::NIL, "", 0}),
        statements(std::move(statements)) {}

  std::vector<std::shared_ptr<Statement>> statements;
};
} // namespace lox::ast::stmt

#endif