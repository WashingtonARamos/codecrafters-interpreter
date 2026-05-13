#ifndef CODECRAFTERS_INTERPRETER_IDENTIFIER_RESOLUTION_CONTEXT_H
#define CODECRAFTERS_INTERPRETER_IDENTIFIER_RESOLUTION_CONTEXT_H
#include "../../ast/expression/expr.h"
#include "../../interpreter/lox_value.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lox::analysis::contexts {

struct IdentifierResolutionContext {
  bool inside_constructor{false};
  bool inside_class{false};
  bool inside_subclass{false};
  bool inside_function{false};
  bool bypass_block_creation{false};

  std::vector<interpreter::InterpreterError> errors;

  // How many environments up an identifier is from its definition
  // 0 if same environment (same block)
  // > 0 if x environments away
  std::unordered_map<const ast::expr::Identifier *, size_t> distances;

  // Scope stack for resolution: each entry is a set of names declared
  // in that scope. Index 0 = outermost local scope, back() = innermost.
  std::vector<std::unordered_set<const ast::expr::Identifier *>> scopes;

  void BeginScope() { scopes.emplace_back(); }

  void EndScope() { scopes.pop_back(); }

  void Declare(const ast::expr::Identifier &identifier) {
    if (!scopes.empty()) {
      if (scopes.size() > 1) {
        auto the_scope = scopes.back();
        for (const auto &declared : the_scope) {
          if (declared->name == identifier.name) {
            errors.emplace_back(
                "Variable with this name already declared in this scope",
                identifier);
            return;
          }
        }
      }
      scopes.back().insert(&identifier);
    }
  }

  const ast::expr::Identifier *Find(const ast::expr::Identifier *id,
                                    const size_t depth) const {
    const auto scope = scopes.at(depth);
    for (const auto &scoped_id : scope) {
      if (scoped_id->name == id->name) {
        return scoped_id;
      }
    }
    return nullptr;
  }

  void ResolveLocal(const ast::expr::Identifier *identifier) {
    for (int depth = static_cast<int>(scopes.size()) - 1; depth >= 0; --depth) {
      if (const auto decl = Find(identifier, depth);
          decl != nullptr && decl->line <= identifier->line) {
        auto dist = scopes.size() - 1 - depth;
        // dist == scopes.size() - 1 => global ref
        if (dist != scopes.size() - 1) {
          distances[identifier] = scopes.size() - 1 - depth;
        }
        return;
      }
    }
  }
};

} // namespace lox::analysis::contexts

#endif
