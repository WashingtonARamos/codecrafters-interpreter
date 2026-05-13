#ifndef CODECRAFTERS_INTERPRETER_FUNCTION_DECLARATION_H
#define CODECRAFTERS_INTERPRETER_FUNCTION_DECLARATION_H
#include "../../lexer/token.h"
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct FunctionDeclaration : Node {
  FunctionDeclaration(const lexer::Token &token, std::shared_ptr<expr::Identifier> name_expr,
                      std::vector<std::shared_ptr<expr::Identifier>> arguments,
                      std::shared_ptr<Block> body)
      : Node(token), name(std::move(name_expr)), arguments(std::move(arguments)),
        body(std::move(body)) {}

  std::shared_ptr<expr::Identifier> name;
  std::vector<std::shared_ptr<expr::Identifier>> arguments;
  std::shared_ptr<Block> body;
};
} // namespace lox::ast::stmt

#endif
