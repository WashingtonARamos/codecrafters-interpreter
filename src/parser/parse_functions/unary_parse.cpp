#include "../../../inc/parser/parse_functions/unary_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Expression;
using ast::expr::LogicalNot;
using ast::expr::UnaryMinus;
using lexer::Token;
using lexer::TokenType;

constexpr auto logical_not_bp = prefix_binding_power(TokenType::BANG);
constexpr auto unary_minus_bp = prefix_binding_power(TokenType::MINUS);

Expression LogicalNotParseFn(Parser &parser, const Token &token) {
  auto expr = parser.ParseExpression(logical_not_bp);
  const auto expr_ptr = std::make_shared<Expression>(std::move(expr));

  return LogicalNot(token, expr_ptr);
}

Expression UnaryMinusParseFn(Parser &parser, const Token &token) {
  auto expr = parser.ParseExpression(unary_minus_bp);
  const auto expr_ptr = std::make_shared<Expression>(std::move(expr));

  return UnaryMinus(token, expr_ptr);
}

} // namespace lox::parser