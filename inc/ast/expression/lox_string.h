#ifndef CODECRAFTERS_INTERPRETER_LOX_STRING_H
#define CODECRAFTERS_INTERPRETER_LOX_STRING_H
#include "../node.h"
#include <memory>

namespace lox::ast::expr {
struct LoxString : Node {
  LoxString(const lexer::Token &token)
      : Node(token), value(token.value) {}

  std::string value;
};
} // namespace lox::ast::expr

#endif
