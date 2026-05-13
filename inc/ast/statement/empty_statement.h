#ifndef CODECRAFTERS_INTERPRETER_EMPTY_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_EMPTY_STATEMENT_H
#include "../../lexer/token.h"
#include "../node.h"

namespace lox::ast::stmt {
struct EmptyStatement : Node {
  explicit EmptyStatement(const lexer::Token &token) : Node(token) {}
};
} // namespace lox::ast::stmt

#endif
