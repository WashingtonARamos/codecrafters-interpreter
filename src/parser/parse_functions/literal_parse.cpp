#include "../../../inc/parser/parse_functions/literal_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Boolean;
using ast::expr::Expression;
using ast::expr::Grouping;
using ast::expr::Identifier;
using ast::expr::LoxString;
using ast::expr::Nil;
using ast::expr::Number;
using lexer::Token;
using lexer::TokenType;

Expression BooleanParseFn(Parser & /*parser*/, const Token &token) {
  return Boolean{token, token.type == TokenType::TRUE};
}

Expression GroupingParseFn(Parser &parser, const Token &token) {
  auto expr = parser.ParseExpression(0);
  parser.Consume(TokenType::RIGHT_PAREN);
  return Grouping(token, std::make_shared<Expression>(std::move(expr)));
}

Expression IdentifierParseFn(Parser & /*parser*/, const Token &token) {
  return Identifier(token);
}

Expression NilParseFn(Parser & /*parser*/, const Token &token) {
  return Nil(token);
}

Expression NumberParseFn(Parser & /*parser*/, const Token &token) {
  return Number(token);
}

Expression StringParseFn(Parser & /*parser*/, const Token &token) {
  return LoxString(token);
}

} // namespace lox::parser
