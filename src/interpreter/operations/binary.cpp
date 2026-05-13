#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/context.h"
#include "../../../inc/interpreter/evaluation_interface.h"

namespace lox::interpreter {

using namespace ast::expr;

// <expr> Op <expr>
template <typename Expr, typename Op>
LoxValue EvaluateBinary(const Expr &expr, const std::shared_ptr<Context> &ctx,
                        Op op) {
  auto left = Evaluate(*expr.left, ctx);
  if (std::holds_alternative<InterpreterError>(left))
    return left;
  auto right = Evaluate(*expr.right, ctx);
  if (std::holds_alternative<InterpreterError>(right))
    return right;

  // Binary operations may return error on type mismatch
  auto op_res = op(left, right);
  if (std::holds_alternative<InterpreterError>(op_res)) {
    auto err = std::get<InterpreterError>(op_res);
    return InterpreterError(err.message, expr);
  }

  return op_res;
}

// <expr> = <expr>
LoxValue Evaluate(const Assignment &expr, const std::shared_ptr<Context> &ctx) {
  auto value = Evaluate(*expr.value, ctx);
  if (std::holds_alternative<InterpreterError>(value))
    return value;

  if (const auto id = std::get_if<Identifier>(&*expr.target)) {
    if (const auto assign_res = ctx->Assign(*id, value);
        assign_res && std::holds_alternative<InterpreterError>(*assign_res))
      return *assign_res;

    return value;
  }

  if (const auto dot = std::get_if<DotOperator>(&*expr.target); dot != nullptr) {
    auto target = Evaluate(*dot->left, ctx);
    if (std::holds_alternative<InterpreterError>(target))
      return target;
    if (!std::holds_alternative<ClassInstance>(target)) {
      return InterpreterError("Can only assign to fields of class instances.",
                              *expr.target);
    }
    if (!std::holds_alternative<Identifier>(*dot->right)) {
      return InterpreterError("Can only assign to fields with identifier names.",
                              *expr.target);
    }

    const auto identifier = std::get<Identifier>(*dot->right);
    const auto instance = std::get<ClassInstance>(target);
    if (!instance.ctx->HasLocal(identifier)) {
      if (const auto declare_res = instance.ctx->Declare(identifier);
          declare_res && std::holds_alternative<InterpreterError>(*declare_res))
        return *declare_res;
    }
    if (const auto assign_res = instance.ctx->Assign(identifier, value);
        assign_res && std::holds_alternative<InterpreterError>(*assign_res))
      return *assign_res;
    return value;
  }

  return InterpreterError("Unable to assign", *expr.target);
}

// <expr> + <expr>
LoxValue Evaluate(const Addition &expr, const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::plus{});
}

// <expr> / <expr>
LoxValue Evaluate(const Division &expr, const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::divides{});
}

// <expr> * <expr>
LoxValue Evaluate(const Multiplication &expr,
                  const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::multiplies{});
}

// <expr> - <expr>
LoxValue Evaluate(const Subtraction &expr,
                  const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::minus{});
}

// <expr> == <expr>
LoxValue Evaluate(const Equality &expr, const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::equal_to{});
}

// <expr> != <expr>
LoxValue Evaluate(const Inequality &expr, const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::not_equal_to{});
}

// <expr> > <expr>
LoxValue Evaluate(const GreaterThan &expr,
                  const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::greater{});
}

// <expr> < <expr>
LoxValue Evaluate(const LessThan &expr, const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::less{});
}

// <expr> >= <expr>
LoxValue Evaluate(const GreaterOrEqualTo &expr,
                  const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::greater_equal{});
}

// <expr> <= <expr>
LoxValue Evaluate(const LessOrEqualTo &expr,
                  const std::shared_ptr<Context> &ctx) {
  return EvaluateBinary(expr, ctx, std::less_equal{});
}

// <expr> or <expr>
LoxValue Evaluate(const Or &expr, const std::shared_ptr<Context> &ctx) {
  if (const auto left = Evaluate(*expr.left, ctx); is_truthy(left)) {
    return left;
  }
  return Evaluate(*expr.right, ctx);
}

// <expr> and <expr>
LoxValue Evaluate(const And &expr, const std::shared_ptr<Context> &ctx) {
  if (const auto left = Evaluate(*expr.left, ctx); !is_truthy(left)) {
    return left;
  }
  return Evaluate(*expr.right, ctx);
}

} // namespace lox::interpreter