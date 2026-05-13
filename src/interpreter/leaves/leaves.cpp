#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/evaluation_interface.h"

namespace lox::interpreter {

LoxValue Evaluate(const ast::expr::Boolean &expr,
                  const std::shared_ptr<Context> & /*ctx*/) {
  return expr.value;
}

LoxValue Evaluate(const ast::expr::Number &expr,
                  const std::shared_ptr<Context> & /*ctx*/) {
  return expr.value;
}

LoxValue Evaluate(const ast::expr::LoxString &expr,
                  const std::shared_ptr<Context> & /*ctx*/) {
  return expr.value;
}

LoxValue Evaluate(const ast::expr::Nil & /*expr*/,
                  const std::shared_ptr<Context> & /*ctx*/) {
  return std::monostate();
}

} // namespace lox::interpreter
