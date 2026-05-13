#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/ast/statement/statement.h"
#include "../../../inc/parser/parse_functions/function_parse.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Assignment;
using ast::expr::FunctionCall;
using ast::expr::Expression;
using ast::expr::Identifier;
using ast::expr::Nil;
using ast::stmt::Block;
using ast::stmt::Statement;
using ast::stmt::FunctionDeclaration;
using ast::stmt::ExpressionStatement;
using lexer::Token;
using lexer::TokenType;

Statement FunctionDeclarationParseFn(Parser &parser,
                                                 const Token &token) {
  if (parser.CurrentToken().type != TokenType::IDENTIFIER) {
    parser.ReportError(parser.CurrentToken());
    return ExpressionStatement(token, nullptr);
  }
  const auto name_token = parser.CurrentToken();
  parser.Advance();
  const auto name = std::make_shared<Identifier>(name_token);

  parser.Consume(TokenType::LEFT_PAREN);
  std::vector<std::shared_ptr<Identifier>> arguments;

  if (parser.CurrentToken().type != TokenType::RIGHT_PAREN) {
    auto expr = parser.ParseExpression(0);
    const auto id = std::get_if<Identifier>(&expr);
    if (id == nullptr) {
      parser.ReportError(token);
      return ExpressionStatement(token, nullptr);
    }
    arguments.push_back(std::make_shared<Identifier>(*id));

    while (parser.CurrentToken().type == TokenType::COMMA) {
      parser.Advance();
      expr = parser.ParseExpression(0);
      const auto another_id = std::get_if<Identifier>(&expr);
      if (another_id == nullptr) {
        parser.ReportError(token);
        return ExpressionStatement(token, nullptr);
      }

      arguments.push_back(std::make_shared<Identifier>(*another_id));
    }
  }

  parser.Consume(TokenType::RIGHT_PAREN);
  if (parser.CurrentToken().type != TokenType::LEFT_BRACE) {
    parser.ReportError(token);
    return ExpressionStatement(token, nullptr);
  }

  auto body = parser.ParseStatement();
  if (!std::holds_alternative<Block>(body)) {
    parser.ReportError(token);
    return ExpressionStatement(token, nullptr);
  }

  const auto body_ptr = std::make_shared<Block>(std::get<Block>(body));
  return FunctionDeclaration(token, name, arguments, body_ptr);
}

Expression FunctionCallParseFn(Parser &parser, const Token &token,
                             const std::shared_ptr<Expression> &left) {
  std::vector<std::shared_ptr<Expression>> arguments;

  if (parser.CurrentToken().type != TokenType::RIGHT_PAREN) {
    arguments.push_back(std::make_shared<Expression>(parser.ParseExpression(0)));
    while (parser.CurrentToken().type == TokenType::COMMA) {
      parser.Advance();
      arguments.push_back(std::make_shared<Expression>(parser.ParseExpression(0)));
    }
  }

  parser.Consume(TokenType::RIGHT_PAREN);
  return FunctionCall(token, left, arguments);
}

} // namespace lox::parser