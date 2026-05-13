#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/context.h"
#include "../../../inc/interpreter/evaluation_interface.h"

namespace lox::interpreter {

using namespace ast::expr;

LoxValue Evaluate(const DotOperator &expr,
                  const std::shared_ptr<Context> &ctx) {
  auto left = Evaluate(*expr.left, ctx);
  if (std::holds_alternative<InterpreterError>(left))
    return left;

  if (!std::holds_alternative<ClassInstance>(left)) {
    return InterpreterError("Can only access fields of class instances.", expr);
  }

  auto instance = std::get<ClassInstance>(left);
  if (!(std::holds_alternative<Identifier>(*expr.right) ||
        std::holds_alternative<FunctionCall>(*expr.right))) {
    return InterpreterError("Can only access fields with identifier names.",
                            *expr.right);
  }

  instance.ctx->outer_context = ctx;
  auto res = Evaluate(*expr.right, instance.ctx);
  if (std::holds_alternative<InterpreterError>(res))
    return res;

  if (const auto *func_called = std::get_if<FunctionCall>(&*expr.right)) {
    if (const auto *name = std::get_if<Identifier>(&*func_called->callee);
        name && name->name == "init") {
      return instance;
    }
  }

  return res;
}
} // namespace lox::interpreter