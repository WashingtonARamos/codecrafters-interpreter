#ifndef CODECRAFTERS_INTERPRETER_INTERPRETER_ERROR_H
#define CODECRAFTERS_INTERPRETER_INTERPRETER_ERROR_H
#include "../ast/statement/statement.h"

namespace lox::interpreter {

struct InterpreterError {
  std::string message;
  uint32_t line{0};

  explicit InterpreterError(std::string message)
      : message(std::move(message)) {}
  explicit InterpreterError(std::string message, const uint32_t line)
      : message(std::move(message)), line(line) {}
  explicit InterpreterError(std::string message,
                            const ast::stmt::Statement &stmt)
      : message(std::move(message)), line(get_line(stmt)) {}
  explicit InterpreterError(std::string message,
                            const ast::expr::Expression &expr)
      : message(std::move(message)), line(get_line(expr)) {}

  std::string ToString() const {
    return "[line " + std::to_string(line) + "] " + message;
  }
};

} // namespace lox::interpreter

#endif