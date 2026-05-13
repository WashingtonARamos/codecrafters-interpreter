#include "../../../inc/parser/parse_functions/access_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::DotOperator;
using ast::expr::Expression;
using ast::expr::Identifier;
using lexer::Token;
using lexer::TokenType;

constexpr auto dot_rbp = infix_binding_power(TokenType::DOT).rbp;

Expression DotOperatorParseFn(Parser &parser, const Token &token,
                              const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(dot_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));
  return DotOperator(token, left, right_ptr);
}

Expression ThisOperatorParseFn(Parser & /*parser*/, const Token &token) {
  return Identifier(token);
}

Expression SuperParseFn(Parser & parser, const Token &token) {
  if (parser.CurrentToken().type != TokenType::DOT) {
    parser.ReportError(token);
    return Identifier(token);
  }
  return Identifier(token);
}

} // namespace lox::parser