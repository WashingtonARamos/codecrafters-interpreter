#include "../../../inc/ast/statement/statement.h"
#include "../../../inc/interpreter/context.h"
#include "../../../inc/interpreter/evaluation_interface.h"
#include "../../../inc/interpreter/lox_value.h"

#include <iostream>

namespace lox::interpreter {

// All statements other than return should return a nullptr
// If any statement receives anything but nullptr from another statement,
// it should bubble it up immediately, same for errors coming from evaluations

using namespace lox::ast::stmt;

std::shared_ptr<LoxValue> Execute(const Block &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  const auto block_ctx = ctx->Derive();

  for (const auto &statement : stmt.statements) {
    if (auto val = Execute(*statement, block_ctx)) {
      return val;
    }
  }

  return nullptr;
}

// class <identifier> [< <superclass>] <block>
std::shared_ptr<LoxValue> Execute(const ClassDeclaration &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  if (auto err = ctx->Declare(*stmt.name);
      err && std::holds_alternative<InterpreterError>(*err))
    return err;

  std::shared_ptr<ClassBlueprint> super_ptr = nullptr;
  if (stmt.superclass) {
    auto res = Evaluate(*stmt.superclass, ctx);
    if (!std::holds_alternative<ClassBlueprint>(res)) {
      return make_error(std::string{"Superclass must be a class"},
                        *stmt.superclass);
    }
    super_ptr = std::make_shared<ClassBlueprint>(std::get<ClassBlueprint>(res));
  }

  const auto class_blueprint =
      ClassBlueprint(stmt.name->name, super_ptr, ctx, stmt.methods);
  if (auto assign_res = ctx->Assign(*stmt.name, class_blueprint);
      assign_res && std::holds_alternative<InterpreterError>(*assign_res))
    return assign_res;

  return nullptr;
}

// var <identifier> = <expr>;
std::shared_ptr<LoxValue> Execute(const VariableDeclaration &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  std::shared_ptr<LoxValue> val = nullptr;
  if (stmt.initializer) {
    auto eval_res = Evaluate(*stmt.initializer, ctx);
    if (std::holds_alternative<InterpreterError>(eval_res))
      return make_error(eval_res, *stmt.initializer);

    val = std::make_shared<LoxValue>(eval_res);
  }

  ctx->Declare(*stmt.name);
  if (val)
    ctx->Assign(*stmt.name, *val);

  return nullptr;
}

// <expr>
std::shared_ptr<LoxValue> Execute(const ExpressionStatement &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  if (const auto expression_value = Evaluate(*stmt.expression, ctx);
      std::holds_alternative<InterpreterError>(expression_value))
    return make_error(expression_value, *stmt.expression);

  return nullptr;
}

// print <expr>
std::shared_ptr<LoxValue> Execute(const PrintStatement &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  const auto expr_val = Evaluate(*stmt.expression, ctx);
  if (std::holds_alternative<InterpreterError>(expr_val))
    return make_error(expr_val, *stmt.expression);

  std::cout << ToString(expr_val) << std::endl;
  return nullptr;
}

// if <condition> { <if_body> } else { <else_stmt> }
std::shared_ptr<LoxValue> Execute(const IfStatement &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  const auto condition_value = Evaluate(*stmt.condition, ctx);
  if (std::holds_alternative<InterpreterError>(condition_value))
    return make_error(condition_value, *stmt.condition);

  if (is_truthy(condition_value)) {
    if (auto if_val = Execute(*stmt.if_stmt, ctx))
      return if_val;
  } else if (stmt.else_stmt) {
    if (auto else_val = Execute(*stmt.else_stmt, ctx))
      return else_val;
  }

  return nullptr;
}

// for (<stmt>; <expr; <expr>) <expr>
std::shared_ptr<LoxValue> Execute(const For &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  const auto for_pre_ctx = ctx->Derive();

  if (auto init_val = Execute(*stmt.initializer, for_pre_ctx))
    return init_val;

  const auto for_ctx = for_pre_ctx->Derive();
  const bool should_bypass_env_creation =
      stmt.body && std::holds_alternative<Block>(*stmt.body);

  while (true) {
    auto condition_val = Evaluate(*stmt.condition, for_ctx);
    if (std::holds_alternative<InterpreterError>(condition_val))
      return make_error(condition_val, *stmt.condition);
    if (!is_truthy(condition_val))
      break;

    for_ctx->bypass_env_creation = should_bypass_env_creation;
    if (auto exec_res = Execute(*stmt.body, for_ctx))
      return exec_res;

    if (stmt.increment) {
      if (const auto increment_val = Evaluate(*stmt.increment, for_ctx);
          std::holds_alternative<InterpreterError>(increment_val))
        return make_error(increment_val, *stmt.increment);
    }
  }

  return nullptr;
}

// while (<expr) <stmt>
std::shared_ptr<LoxValue> Execute(const While &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  while (true) {
    auto condition_val = Evaluate(*stmt.condition, ctx);
    if (std::holds_alternative<InterpreterError>(condition_val))
      return make_error(condition_val, *stmt.condition);
    if (!is_truthy(condition_val))
      break;

    if (auto exec_res = Execute(*stmt.body, ctx))
      return exec_res;
  }

  return nullptr;
}

// Empty statement does nothing and returns nothing, it's literally a ;
std::shared_ptr<LoxValue> Execute(const EmptyStatement & /*stmt */,
                                  const std::shared_ptr<Context> & /*env*/) {
  return nullptr;
}

// return <expr>
std::shared_ptr<LoxValue> Execute(const Return &stmt,
                                  const std::shared_ptr<Context> &ctx) {
  if (stmt.value) {
    auto value = Evaluate(*stmt.value, ctx);
    return std::make_shared<LoxValue>(value);
  }

  return std::make_shared<LoxValue>();
}

} // namespace lox::interpreter