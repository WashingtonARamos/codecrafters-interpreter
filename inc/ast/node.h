#ifndef CODECRAFTERS_INTERPRETER_NODE_H
#define CODECRAFTERS_INTERPRETER_NODE_H
#include <cstdint>

struct Node {
  explicit Node(const lox::lexer::Token &token) : line(token.line), column(token.column) {}
  uint32_t line;
  uint32_t column;
};

#endif
