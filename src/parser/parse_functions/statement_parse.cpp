#include "../../../inc/parser/parse_functions/statement_parse.h"
#include "../../../inc/ast/expression/expr.h"
#include "../../../inc/ast/statement/statement.h"
#include "../../../inc/parser/binding_power.h"
#include "../../../inc/parser/parse_functions/function_parse.h"
#include "../../../inc/parser/parser.h"

namespace lox::parser {

// Bring what you need
using ast::expr::Expression;
using ast::expr::Identifier;
using ast::stmt::Block;
using ast::stmt::ClassDeclaration;
using ast::stmt::EmptyStatement;
using ast::stmt::ExpressionStatement;
using ast::stmt::For;
using ast::stmt::IfStatement;
using ast::stmt::PrintStatement;
using ast::stmt::Return;
using ast::stmt::Statement;
using ast::stmt::VariableDeclaration;
using ast::stmt::While;

using lexer::TokenType;

// { }
Statement BlockParseFn(Parser &parser, const lexer::Token &token) {
  std::vector<std::shared_ptr<Statement>> statements;
  bool found_closing_curly_brace = false;
  while (parser.CurrentToken().type != TokenType::END_OF_FILE) {
    if (parser.CurrentToken().type == TokenType::RIGHT_BRACE) {
      parser.Consume(TokenType::RIGHT_BRACE);
      found_closing_curly_brace = true;
      break;
    }

    auto next_statement = parser.ParseStatement();
    auto next_statement_ptr = std::make_shared<Statement>(next_statement);
    statements.push_back(next_statement_ptr);
  }

  if (!found_closing_curly_brace) {
    parser.ReportError(parser.CurrentToken());
  }

  return Block{token, statements};
}

// ;
Statement EmptyStatementParseFn(Parser &parser, const lexer::Token &token) {
  if (parser.CurrentToken().type == TokenType::SEMICOLON) {
    parser.Advance();
    return ExpressionStatement(token, nullptr);
  }
  return EmptyStatement(token);
}

Statement ClassDeclarationParseFn(Parser &parser, const lexer::Token &token) {
  if (parser.CurrentToken().type != TokenType::IDENTIFIER) {
    parser.ReportError(parser.CurrentToken());
    return ClassDeclaration(token, nullptr, nullptr, {});
  }

  const auto name = std::make_shared<Identifier>(parser.CurrentToken());
  parser.Advance();

  const std::shared_ptr<Identifier> superclass =
      [&]() -> std::shared_ptr<Identifier> {
    if (parser.CurrentToken().type != TokenType::LESS_THAN) {
      return nullptr;
    }
    parser.Advance();
    if (parser.CurrentToken().type != TokenType::IDENTIFIER) {
      parser.ReportError(parser.CurrentToken());
      return nullptr;
    }
    auto res = std::make_shared<Identifier>(parser.CurrentToken());
    parser.Advance();
    return res;
  }();

  if (parser.CurrentToken().type != TokenType::LEFT_BRACE) {
    parser.ReportError(parser.CurrentToken());
    return ClassDeclaration(token, name, nullptr, {});
  }
  parser.Advance();
  std::vector<std::shared_ptr<ast::stmt::FunctionDeclaration>> methods;

  while (parser.CurrentToken().type != TokenType::RIGHT_BRACE) {
    const auto next_type = parser.CurrentToken().type;
    if (next_type == TokenType::IDENTIFIER) {
      if (auto fun = FunctionDeclarationParseFn(parser, parser.CurrentToken());
          std::holds_alternative<ast::stmt::FunctionDeclaration>(fun)) {
        auto fun_ptr = std::make_shared<ast::stmt::FunctionDeclaration>(
            std::get<ast::stmt::FunctionDeclaration>(fun));
        methods.push_back(fun_ptr);
        continue;
      }
    }
    if (next_type != TokenType::RIGHT_BRACE) {
      parser.ReportError(parser.CurrentToken());
      return ClassDeclaration(token, name, superclass, {});
    }
  }
  parser.Consume(TokenType::RIGHT_BRACE);
  return ClassDeclaration(token, name, superclass, methods);
}

// for (<expr>; <expr>; <expr>) <statement>
Statement ForParseFn(Parser &parser, const lexer::Token &token) {
  if (parser.CurrentToken().type != TokenType::LEFT_PAREN) {
    parser.ReportError(parser.CurrentToken());
    return ExpressionStatement(token, nullptr);
  }

  std::shared_ptr<Expression> increment_ptr = nullptr;
  parser.Advance();
  auto initializer = parser.ParseStatement();
  auto condition = parser.ParseExpression(0);
  parser.Consume(TokenType::SEMICOLON);
  if (parser.CurrentToken().type != TokenType::RIGHT_PAREN) {
    increment_ptr = std::make_shared<Expression>(parser.ParseExpression(0));
  }

  parser.Consume(TokenType::RIGHT_PAREN);
  auto body = parser.ParseStatement();

  return For(token, std::make_shared<Statement>(initializer),
             std::make_shared<Expression>(condition), increment_ptr,
             std::make_shared<Statement>(body));
}

// if <expr>
Statement IfParseFn(Parser &parser, const lexer::Token &token) {
  const auto condition = parser.ParseExpression(0);
  const auto condition_ptr = std::make_shared<Expression>(condition);
  std::shared_ptr<Statement> else_body_ptr = nullptr;

  const auto if_body = parser.ParseStatement();
  const auto if_body_ptr = std::make_shared<Statement>(if_body);

  if (parser.CurrentToken().type == TokenType::ELSE) {
    parser.Advance();
    else_body_ptr = std::make_shared<Statement>(parser.ParseStatement());
  }

  return IfStatement(token, condition_ptr, if_body_ptr, else_body_ptr);
}

// print <expr>
Statement PrintParseFn(Parser &parser, const lexer::Token &token) {
  const auto expr = parser.ParseExpression(0);
  const auto expr_ptr = std::make_shared<Expression>(expr);
  parser.Consume(TokenType::SEMICOLON);
  return PrintStatement(token, expr_ptr);
}

// return <expr>
Statement ReturnStatementParseFn(Parser &parser, const lexer::Token &token) {
  std::shared_ptr<Expression> value = nullptr;
  if (parser.CurrentToken().type != TokenType::SEMICOLON) {
    value = std::make_shared<Expression>(parser.ParseExpression(0));
  }

  parser.Consume(TokenType::SEMICOLON);
  return Return(token, value);
}

// var <identifier> = <expr>;
Statement VarParseFn(Parser &parser, const lexer::Token &token) {
  if (parser.CurrentToken().type != TokenType::IDENTIFIER) {
    parser.ReportError(parser.CurrentToken());
    return ExpressionStatement(token, nullptr);
  }

  const auto name = std::make_shared<Identifier>(parser.CurrentToken());
  parser.Advance();

  std::shared_ptr<Expression> initializer = nullptr;
  if (parser.CurrentToken().type == TokenType::ASSIGN) {
    parser.Advance();
    initializer = std::make_shared<Expression>(parser.ParseExpression(0));
  }

  parser.Consume(TokenType::SEMICOLON);
  return VariableDeclaration(token, name, initializer);
}

// while <expr> <statement>
Statement WhileParseFn(Parser &parser, const lexer::Token &token) {
  const auto condition = parser.ParseExpression(0);
  const auto body = parser.ParseStatement();
  return While(token, std::make_shared<Expression>(condition),
               std::make_shared<Statement>(body));
}

} // namespace lox::parser