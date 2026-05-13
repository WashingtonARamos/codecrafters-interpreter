#ifndef CODECRAFTERS_INTERPRETER_BOOLEAN_H
#define CODECRAFTERS_INTERPRETER_BOOLEAN_H
#include "../node.h"

namespace lox::ast::expr {
struct Boolean : Node {
  Boolean(const lexer::Token &token, bool val)
      : Node(token), value(val) {}

  bool value;
};
} // namespace lox::ast::expr

#endif
