#ifndef CODECRAFTERS_INTERPRETER_VARIABLE_DECLARATION_H
#define CODECRAFTERS_INTERPRETER_VARIABLE_DECLARATION_H
#include "../../lexer/token.h"
#include "../node.h"
#include <memory>
#include <utility>

namespace lox::ast::stmt {
struct VariableDeclaration : Node {
  VariableDeclaration(const lexer::Token &token,
                      std::shared_ptr<expr::Identifier> name,
                      std::shared_ptr<expr::Expression> initializer)
      : Node(token), name(std::move(name)),
        initializer(std::move(initializer)) {}

  std::shared_ptr<expr::Identifier> name;
  std::shared_ptr<expr::Expression> initializer;
};
} // namespace lox::ast::stmt

#endif
