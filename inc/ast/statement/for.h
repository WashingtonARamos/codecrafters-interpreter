#ifndef CODECRAFTERS_INTERPRETER_FOR_H
#define CODECRAFTERS_INTERPRETER_FOR_H
#include "../../lexer/token.h"
#include "../expression/fwd/expr.h"
#include "../node.h"
#include "fwd/statement.h"
#include <memory>

namespace lox::ast::stmt {
struct For : Node {
  For(const lexer::Token &token,
      const std::shared_ptr<Statement> &initializer,
      const std::shared_ptr<expr::Expression> &condition,
      const std::shared_ptr<expr::Expression> &increment,
      const std::shared_ptr<Statement> &body)
      : Node(token), initializer(initializer), condition(condition),
        increment(increment), body(body) {}

  std::shared_ptr<Statement> initializer;
  std::shared_ptr<expr::Expression> condition;
  std::shared_ptr<expr::Expression> increment;
  std::shared_ptr<Statement> body;
};
} // namespace lox::ast::stmt

#endif
