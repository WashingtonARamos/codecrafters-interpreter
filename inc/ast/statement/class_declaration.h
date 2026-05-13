#ifndef CODECRAFTERS_INTERPRETER_CLASS_DECLARATION_H
#define CODECRAFTERS_INTERPRETER_CLASS_DECLARATION_H
#include "../../ast/expression/expr.h"
#include "../../lexer/token.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct ClassDeclaration : Node {
  ClassDeclaration(const lexer::Token &token,
                   std::shared_ptr<expr::Identifier> name,
                   std::shared_ptr<expr::Identifier> superclass,
                   std::vector<std::shared_ptr<FunctionDeclaration>> methods)
      : Node(token), name(std::move(name)), superclass(std::move(superclass)),
        methods(std::move(methods)) {}

  std::shared_ptr<expr::Identifier> name;
  std::shared_ptr<expr::Identifier> superclass;
  std::vector<std::shared_ptr<FunctionDeclaration>> methods;
};
} // namespace lox::ast::stmt

#endif
