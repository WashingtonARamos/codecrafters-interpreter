#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/context.h"
#include "../../../inc/interpreter/evaluation_interface.h"

namespace lox::interpreter {

LoxValue Evaluate(const ast::expr::Grouping &expr,
                  const std::shared_ptr<Context> &ctx) {
  return Evaluate(*expr.expression, ctx);
}

LoxValue Evaluate(const ast::expr::Identifier &expr,
                  const std::shared_ptr<Context> &ctx) {
  const auto val = ctx->Get(expr);
  if (!val) {
    return *make_error("Undefined variable '" + expr.name + "'.", expr);
  }

  return *val;
}

} // namespace lox::interpreter
