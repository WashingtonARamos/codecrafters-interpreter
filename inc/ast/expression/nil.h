#ifndef CODECRAFTERS_INTERPRETER_NIL_H
#define CODECRAFTERS_INTERPRETER_NIL_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct Nil : Node {
  explicit Nil(const lexer::Token &token) : Node(token) {}
};
} // namespace lox::ast::expr

#endif