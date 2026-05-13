#ifndef CODECRAFTERS_INTERPRETER_RETURN_H
#define CODECRAFTERS_INTERPRETER_RETURN_H
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"

namespace lox::ast::stmt {
struct Return : Node {
  Return(const lexer::Token &token, std::shared_ptr<expr::Expression> value)
      : Node(token), value(std::move(value)) {}
  std::shared_ptr<expr::Expression> value;
};

} // namespace lox::ast::stmt

#endif
