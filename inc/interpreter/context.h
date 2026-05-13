#ifndef CODECRAFTERS_INTERPRETER_CONTEXT_H
#define CODECRAFTERS_INTERPRETER_CONTEXT_H
#include "../../inc/ast/expression/expr.h"
#include "environment.h"

#include <memory>
#include <unordered_map>

namespace lox::interpreter {
struct Context {
  std::shared_ptr<Environment> global_env;
  std::shared_ptr<Environment> current_env;
  std::unordered_map<const ast::expr::Identifier *, size_t> locals;
  std::shared_ptr<Context> outer_context;
  bool bypass_env_creation{false};

  // Returns a new Context with the same global_env and locals but a new
  // current_env unless bypassing the env creation is requested, such as in
  // function calls, who already create their own environments and pass it down
  // to the block
  [[nodiscard]] std::shared_ptr<Context> Derive() {
    if (bypass_env_creation) {
      bypass_env_creation = false;
      return std::make_shared<Context>(*this);
    }
    auto child_env = std::make_shared<Environment>(current_env);
    return std::make_shared<Context>(global_env, child_env, locals);
  }

  std::shared_ptr<LoxValue> Assign(const ast::expr::Identifier &expr,
                                   const LoxValue &value);
  std::shared_ptr<LoxValue> Declare(const ast::expr::Identifier &expr);
  std::shared_ptr<LoxValue> Get(const ast::expr::Identifier &expr) const;

  // Checks if the current environment has a local variable with the given
  // identifier, usable mostly for class instances
  bool HasLocal(const ast::expr::Identifier &expr) const;
};
} // namespace lox::interpreter

#endif
