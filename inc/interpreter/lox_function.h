#ifndef CODECRAFTERS_INTERPRETER_LOX_FUNCTION_H
#define CODECRAFTERS_INTERPRETER_LOX_FUNCTION_H
#include "../ast/statement/statement.h"
#include <string>
#include <utility>
#include <vector>

namespace lox::interpreter {

struct Context;

struct LoxFunction {
  LoxFunction(std::string name, const std::vector<std::string> &parameters,
              const std::shared_ptr<ast::stmt::Block> &body,
              std::shared_ptr<Context> context)
      : name(std::move(name)), parameters(parameters), body(body),
        context(std::move(context)) {}

  std::string name;
  std::vector<std::string> parameters;
  std::shared_ptr<ast::stmt::Block> body;
  std::shared_ptr<Context> context;
};
} // namespace lox::interpreter

#endif