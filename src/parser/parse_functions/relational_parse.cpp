#include "../../../inc/parser/parse_functions/relational_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::And;
using ast::expr::Equality;
using ast::expr::Expression;
using ast::expr::GreaterOrEqualTo;
using ast::expr::GreaterThan;
using ast::expr::Inequality;
using ast::expr::LessOrEqualTo;
using ast::expr::LessThan;
using ast::expr::Or;
using lexer::Token;
using lexer::TokenType;

constexpr auto equals_rbp = infix_binding_power(TokenType::EQUALS).rbp;
constexpr auto inequality_rbp = infix_binding_power(TokenType::UNEQUAL).rbp;
constexpr auto greater_than_rbp =
    infix_binding_power(TokenType::GREATER_THAN).rbp;
constexpr auto greater_than_or_equal_rbp =
    infix_binding_power(TokenType::GREATER_OR_EQUAL_TO).rbp;
constexpr auto less_than_rbp = infix_binding_power(TokenType::LESS_THAN).rbp;
constexpr auto less_than_or_equal_rbp =
    infix_binding_power(TokenType::LESS_OR_EQUAL_TO).rbp;
constexpr auto or_rbp = infix_binding_power(TokenType::OR).rbp;
constexpr auto and_rbp = infix_binding_power(TokenType::AND).rbp;

// ==
Expression EqualsParseFn(Parser &parser, const Token &token,
                         const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(equals_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Equality(token, left, right_ptr);
}

// !=
Expression UnequalParseFn(Parser &parser, const Token &token,
                          const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(inequality_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Inequality(token, left, right_ptr);
}

// >
Expression GreaterThanParseFn(Parser &parser, const Token &token,
                              const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(greater_than_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return GreaterThan(token, left, right_ptr);
}

// >=
Expression GreaterOrEqualToParseFn(Parser &parser, const Token &token,
                                   const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(greater_than_or_equal_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return GreaterOrEqualTo(token, left, right_ptr);
}

// <
Expression LessThanParseFn(Parser &parser, const Token &token,
                           const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(less_than_or_equal_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return LessThan(token, left, right_ptr);
}

// <=
Expression LessOrEqualToParseFn(Parser &parser, const Token &token,
                                const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(less_than_or_equal_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return LessOrEqualTo(token, left, right_ptr);
}

// OR
Expression OrParseFn(Parser &parser, const Token &token,
                     const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(or_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return Or(token, left, right_ptr);
}

// AND
Expression AndParseFn(Parser &parser, const Token &token,
                      const std::shared_ptr<Expression> &left) {
  auto right = parser.ParseExpression(and_rbp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));

  return And(token, left, right_ptr);
}

} // namespace lox::parser
