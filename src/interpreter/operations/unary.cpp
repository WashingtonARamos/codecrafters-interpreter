#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/evaluation_interface.h"

namespace lox::interpreter {

LoxValue Evaluate(const ast::expr::UnaryMinus &expr,
                  const std::shared_ptr<Context> &ctx) {
  auto value = Evaluate(*expr.right, ctx);
  if (std::holds_alternative<InterpreterError>(value))
    return value;

  if (const auto * double_val = std::get_if<double>(&value))
    return *double_val * -1;

  return InterpreterError("Operand must be a number", expr);
}

LoxValue Evaluate(const ast::expr::LogicalNot &expr,
                  const std::shared_ptr<Context> &ctx) {
  auto value = Evaluate(*expr.right, ctx);
  if (std::holds_alternative<InterpreterError>(value))
    return value;
  return !is_truthy(value);
}

}