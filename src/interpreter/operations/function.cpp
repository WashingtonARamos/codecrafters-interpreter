#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/interpreter/context.h"
#include "../../../inc/interpreter/evaluation_interface.h"

#include <stack>

namespace lox::interpreter {

using namespace ast::expr;

std::shared_ptr<LoxValue> InvokeFunction(const LoxFunction &func,
                                         const std::shared_ptr<Context> &ctx,
                                         const std::vector<LoxValue> &args) {
  if (func.parameters.size() != args.size())
    return make_error("Expected " + std::to_string(func.parameters.size()) +
                      " parameters, got " + std::to_string(args.size()));

  const auto func_env =
      std::make_shared<Environment>(func.context->current_env);
  for (size_t i = 0; i < func.parameters.size(); ++i) {
    if (auto res = func_env->Declare(func.parameters[i]); res != nullptr) {
      return make_error("Failed to declare parameter " + func.parameters[i]);
    }
    if (auto res = func_env->Assign(func.parameters[i], args[i]);
        res != nullptr) {
      return make_error("Failed to assign to parameter " + func.parameters[i]);
    }
  }

  auto func_ctx = Context{ctx->global_env, func_env, ctx->locals};
  func_ctx.bypass_env_creation = true;
  const auto func_ctx_ptr = std::make_shared<Context>(func_ctx);
  if (const auto exec_res = Execute(*func.body, func_ctx_ptr);
      exec_res != nullptr)
    return exec_res;

  return std::make_shared<LoxValue>();
}

std::shared_ptr<LoxValue>
InvokeConstructor(const std::shared_ptr<ClassBlueprint> &blueprint,
                  const std::vector<LoxValue> &args,
                  bool ignore_constructor = false) {
  const auto instance_context = blueprint->context->Derive();
  std::shared_ptr<LoxValue> constructor = nullptr;

  auto instance = ClassInstance(blueprint, instance_context);
  // oooo hacky
  const auto dummy_this =
      Identifier(lexer::Token{lexer::TokenType::IDENTIFIER, "this", 0, 0});
  if (auto decl = instance.ctx->Declare(dummy_this);
      decl && std::holds_alternative<InterpreterError>(*decl))
    return decl;
  if (auto assign = instance.ctx->Assign(dummy_this, instance);
      assign && std::holds_alternative<InterpreterError>(*assign))
    return assign;

  std::vector<ClassBlueprint> bp_list;
  auto cur_bp = *blueprint;
  bp_list.push_back(cur_bp);
  while (cur_bp.superclass) {
    cur_bp = *cur_bp.superclass;
    bp_list.push_back(cur_bp);
  }
  std::reverse(bp_list.begin(), bp_list.end());

  std::unordered_map<std::string, std::shared_ptr<ClassInstance>> super_map;
  for (const auto &bp : bp_list) {
    if (bp.superclass) {
      auto super_val = InvokeConstructor(bp.superclass, args, true);
      if (std::holds_alternative<InterpreterError>(*super_val)) {
        return super_val;
      }
      super_map[bp.name] =
          std::make_shared<ClassInstance>(std::get<ClassInstance>(*super_val));
    }
  }

  if (blueprint->superclass && super_map.contains(blueprint->name)) {
    const auto dummy_super =
        Identifier(lexer::Token{lexer::TokenType::IDENTIFIER, "super", 0, 0});
    if (auto decl = instance_context->Declare(dummy_super);
        decl && std::holds_alternative<InterpreterError>(*decl))
      return decl;
    if (auto assign =
            instance_context->Assign(dummy_super, *super_map[blueprint->name]);
        assign && std::holds_alternative<InterpreterError>(*assign))
      return assign;
  }

  for (const auto &bp : bp_list) {
    for (auto &method : bp.methods) {
      std::vector<std::string> arg_names;
      for (const auto &arg : method->arguments) {
        arg_names.push_back(arg->name);
      }

      auto binding_env = std::make_shared<Environment>(bp.context->current_env);
      if (auto this_decl = binding_env->Declare("this");
          this_decl && std::holds_alternative<InterpreterError>(*this_decl)) {
        return this_decl;
      }
      if (auto this_assign = binding_env->Assign("this", instance);
          this_assign &&
          std::holds_alternative<InterpreterError>(*this_assign)) {
        return this_assign;
      }

      if (auto it = super_map.find(bp.name); it != super_map.end()) {
        if (auto super_decl = binding_env->Declare("super");
            super_decl &&
            std::holds_alternative<InterpreterError>(*super_decl)) {
          return super_decl;
        }
        if (auto super_assign = binding_env->Assign("super", *it->second);
            super_assign &&
            std::holds_alternative<InterpreterError>(*super_assign)) {
          return super_assign;
        }
      }

      auto method_ctx = std::make_shared<Context>(
          Context{bp.context->global_env, binding_env, bp.context->locals});

      const LoxFunction func(method->name->name, arg_names, method->body,
                             method_ctx);
      instance_context->Declare(*method->name);
      instance_context->Assign(*method->name, func);

      if (method->name->name == "init") {
        constructor = instance_context->Get(*method->name);
      }
    }
  }

  if (!ignore_constructor && constructor &&
      std::holds_alternative<LoxFunction>(*constructor)) {
    const auto constructor_func = std::get<LoxFunction>(*constructor);
    if (auto invoke_res =
            InvokeFunction(constructor_func, instance_context, args);
        invoke_res && std::holds_alternative<InterpreterError>(*invoke_res))
      return invoke_res;
  }

  return std::make_shared<LoxValue>(instance);
}

LoxValue Evaluate(const FunctionCall &expr,
                  const std::shared_ptr<Context> &ctx) {
  std::vector<LoxValue> params;
  const auto arg_ctx = ctx->outer_context ? ctx->outer_context : ctx;
  for (const auto &arg_expr : expr.arguments) {
    auto eval_res = Evaluate(*arg_expr, arg_ctx);
    if (std::holds_alternative<InterpreterError>(eval_res))
      return eval_res;
    params.push_back(eval_res);
  }

  if (const auto *id = std::get_if<Identifier>(expr.callee.get())) {
    if (Environment::Builtins.contains(id->name)) {
      const auto builtin = Environment::Builtins.at(id->name);
      return builtin(params);
    }
  }

  auto callee = Evaluate(*expr.callee, ctx);
  if (std::holds_alternative<InterpreterError>(callee))
    return callee;

  if (const auto func = std::get_if<LoxFunction>(&callee); func != nullptr) {
    return *InvokeFunction(*func, func->context, params);
  }

  if (const auto bp = std::get_if<ClassBlueprint>(&callee); bp != nullptr) {
    return *InvokeConstructor(std::make_shared<ClassBlueprint>(*bp), params);
  }

  return InterpreterError("Can only call functions and classes", expr);
}

std::shared_ptr<LoxValue> Execute(const ast::stmt::FunctionDeclaration &expr,
                                  const std::shared_ptr<Context> &ctx) {
  std::vector<std::string> arg_names;
  for (const auto &arg : expr.arguments) {
    arg_names.push_back(arg->name);
  }

  const LoxFunction func(expr.name->name, arg_names, expr.body, ctx);
  ctx->Declare(*expr.name);
  ctx->Assign(*expr.name, func);
  return nullptr;
}
} // namespace lox::interpreter