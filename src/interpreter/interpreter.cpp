#include "../../inc/analysis/tree_analysis.h"
#include "../../inc/ast/expression/expr.h"
#include "../../inc/ast/statement/statement.h"
#include "../../inc/interpreter/lox_value.h"
#include "../../inc/interpreter/context.h"
#include "../../inc/interpreter/evaluation_interface.h"

#include <iostream>

namespace lox::interpreter {

LoxValue Evaluate(const ast::expr::Expression &expr) {
  const auto dummy_token = lexer::Token{};
  const auto dummy_stmt = ast::stmt::EmptyStatement{dummy_token};

  auto global_env = std::make_shared<Environment>(nullptr);
  auto local_env = nullptr;
  auto locals = analysis::ResolveVariables(dummy_stmt);

  const auto ctx =
      std::make_shared<Context>(global_env, local_env, locals.distances);

  return Evaluate(expr, ctx);
}

std::shared_ptr<LoxValue> Execute(const ast::stmt::Program &stmt) {
  auto global_env = std::make_shared<Environment>(nullptr);
  auto local_env = nullptr;
  auto resolution_context = analysis::ResolveVariables(stmt);

  if (!resolution_context.errors.empty()) {
    for (const auto &error : resolution_context.errors) {
      std::cerr << error.ToString() << std::endl;
    }
    auto pre_analysis_error = std::make_shared<LoxValue>(
        InterpreterError("Errors detected during pre-analysis"));
    return pre_analysis_error;
  }

  const auto ctx =
      std::make_shared<Context>(global_env, local_env, resolution_context.distances);

  for (const auto &stmt_ : stmt.statements) {
    if (auto res = Execute(*stmt_, ctx)) {
      return res;
    }
  }
  return nullptr;
}

LoxValue Evaluate(const ast::expr::Expression &expr,
                  const std::shared_ptr<Context> &ctx) {
  return std::visit(
      [&ctx](const auto &node) -> LoxValue { return Evaluate(node, ctx); },
      expr);
}

std::shared_ptr<LoxValue> Execute(const ast::stmt::Statement &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  return std::visit(
      [&ctx]<typename T>(const T &node) -> std::shared_ptr<LoxValue> {
        if constexpr (!std::is_same_v<T, ast::stmt::Program>)
          return Execute(node, ctx);
        return nullptr;
      },
      stmt);
}

std::string ToString(const LoxValue &value) {
  return std::visit(
      []<typename T>(const T &val) -> std::string {
        if constexpr (std::is_same_v<T, std::string>)
          return val;
        else if constexpr (std::is_same_v<T, double>) {
          std::string formatted = std::format("{}", val);
          return formatted;
        } else if constexpr (std::is_same_v<T, bool>)
          return val ? "true" : "false";
        else if constexpr (std::is_same_v<T, std::monostate>)
          return "nil";
        else if constexpr (std::is_same_v<T, InterpreterError>)
          return val.message + '\n' + "[line " + std::to_string(val.line) +
                 ']';
        else if constexpr (std::is_same_v<T, LoxFunction>)
          return "<fn " + val.name + ">";
        else if constexpr (std::is_same_v<T, ClassBlueprint>)
          return val.name;
        else if constexpr (std::is_same_v<T, ClassInstance>)
          return val.blueprint->name + " instance";
        else
          return "null";
      },
      value);
}

} // namespace lox::interpreter