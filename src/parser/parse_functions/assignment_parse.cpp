#include "../../../inc/parser/parse_functions/assignment_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Assignment;
using ast::expr::DotOperator;
using ast::expr::Expression;
using ast::expr::Identifier;
using ast::expr::Nil;
using lexer::Token;
using lexer::TokenType;

constexpr auto assignment_bp = infix_binding_power(TokenType::ASSIGN).rbp;

Expression AssignmentParseFn(Parser &parser, const Token &token,
                             const std::shared_ptr<Expression> &left) {
  if (!(std::holds_alternative<Identifier>(*left) ||
        std::holds_alternative<DotOperator>(*left))) {
    parser.ReportError(token);
    return Nil(token);
  }

  auto right = parser.ParseExpression(assignment_bp);
  const auto right_ptr = std::make_shared<Expression>(std::move(right));
  return Assignment(token, left, right_ptr);
}

} // namespace lox::parser