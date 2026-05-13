#include "../../inc/ast/expression/expr.h"
#include "../../inc/interpreter/context.h"
#include "../../inc/interpreter/lox_value.h"
#include <algorithm>

namespace lox::interpreter {

using namespace ast::expr;

std::shared_ptr<LoxValue> Context::Assign(const Identifier &expr,
                                          const LoxValue &value) {
  if (current_env == nullptr) {
    return global_env->Assign(expr.name, value);
  }

  if (const auto it = locals.find(&expr); it != locals.end()) {
    const size_t distance = it->second;
    return current_env->AssignAt(expr.name, value, distance);
  }

  if (current_env->Contains(expr.name)) {
    return current_env->Assign(expr.name, value);
  }

  return global_env->Assign(expr.name, value);
}

std::shared_ptr<LoxValue> Context::Declare(const Identifier &expr) {
  if (current_env == nullptr) {
    return global_env->Declare(expr.name);
  }

  if (const auto it = locals.find(&expr); it != locals.end()) {
    return make_error("Can't redeclare variable in the same scope");
  }

  return current_env->Declare(expr.name);
}

std::shared_ptr<LoxValue> Context::Get(const Identifier &expr) const {
  if (current_env == nullptr) {
    return global_env->Get(expr.name);
  }

  if (const auto it = locals.find(&expr); it != locals.end()) {
    const size_t distance = it->second;
    return current_env->GetAt(expr.name, distance);
  }

  auto global_val = global_env->Get(expr.name);
  if (global_val != nullptr) {
    return global_val;
  }

  return current_env->GetFromParentRecursive(expr.name);
}

bool Context::HasLocal(const Identifier &expr) const {
  return current_env != nullptr && current_env->Contains(expr.name);
}

} // namespace lox::interpreter
