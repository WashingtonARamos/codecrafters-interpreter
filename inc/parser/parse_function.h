#ifndef CODECRAFTERS_INTERPRETER_PARSELET_H
#define CODECRAFTERS_INTERPRETER_PARSELET_H
#include "../ast/expression/fwd/expr.h"
#include "../ast/statement/fwd/statement.h"
#include "../lexer/token.h"

#include <functional>
#include <memory>

namespace lox::parser {

class Parser;

using PrefixParser =
    std::function<ast::expr::Expression(Parser &, const lexer::Token &)>;
using InfixParser = std::function<ast::expr::Expression(
    Parser &, const lexer::Token &, std::shared_ptr<ast::expr::Expression>)>;
using StatementParser =
    std::function<ast::stmt::Statement(Parser &, const lexer::Token &)>;

} // namespace lox

#endif
