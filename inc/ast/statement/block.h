#ifndef CODECRAFTERS_INTERPRETER_BLOCK_H
#define CODECRAFTERS_INTERPRETER_BLOCK_H
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/statement.h"

#include <memory>
#include <vector>

namespace lox::ast::stmt {

struct Block : Node {
  Block(const lexer::Token &token,
        std::vector<std::shared_ptr<Statement>> statements)
      : Node(token), statements(std::move(statements)) {}
  std::vector<std::shared_ptr<Statement>> statements;
};

} // namespace lox::ast::stmt

#endif
