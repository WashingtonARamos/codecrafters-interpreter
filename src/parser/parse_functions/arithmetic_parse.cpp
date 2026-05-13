#include "../../../inc/parser/parse_functions/arithmetic_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Addition;
using ast::expr::Division;
using ast::expr::Expression;
using ast::expr::Multiplication;
using ast::expr::Subtraction;
using lexer::Token;
using lexer::TokenType;

constexpr auto dot_rbp = infix_binding_power(TokenType::PLUS).rbp;
constexpr auto div_rbp = infix_binding_power(TokenType::SLASH).rbp;
constexpr auto mul_rbp = infix_binding_power(TokenType::STAR).rbp;
constexpr auto sub_rbp = infix_binding_power(TokenType::MINUS).rbp;

// +
Expression AdditionParseFn(Parser &parser, const Token &token,
                           const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(dot_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Addition(token, left, right_ptr);
}

// /
Expression DivisionParseFn(Parser &parser, const Token &token,
                           const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(div_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));
  return Division(token, left, right_ptr);
}

// *
Expression MultiplicationParseFn(Parser &parser, const Token &token,
                                 const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(mul_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Multiplication(token, left, right_ptr);
}

// -
Expression SubtractionParseFn(Parser &parser, const Token &token,
                              const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(sub_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Subtraction(token, left, right_ptr);
}

} // namespace lox::parser