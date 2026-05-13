#ifndef CODECRAFTERS_INTERPRETER_IDENTIFIER_H
#define CODECRAFTERS_INTERPRETER_IDENTIFIER_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct Identifier : Node {
  Identifier(const lexer::Token &token) : Node(token), name(token.value) {}
  std::string name;
};
} // namespace lox::ast::expr

#endif
