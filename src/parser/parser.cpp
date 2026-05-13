#include "../../inc/parser/parser.h"
#include "../../inc/ast/expression/expr.h"
#include "../../inc/ast/statement/statement.h"
#include "../../inc/parser/parse_functions/arithmetic_parse.h"
#include "../../inc/parser/parse_functions/access_parse.h"
#include "../../inc/parser/parse_functions/assignment_parse.h"
#include "../../inc/parser/parse_functions/literal_parse.h"
#include "../../inc/parser/parse_functions/relational_parse.h"
#include "../../inc/parser/parse_functions/statement_parse.h"
#include "../../inc/parser/parse_functions/unary_parse.h"

#include "../../inc/parser/binding_power.h"
#include "../../inc/parser/parse_functions/function_parse.h"
#include <utility>

using namespace lox::lexer;

namespace lox::parser {

Parser::Parser(const Lexer &lexer) : lex_{lexer} {
  RegisterParseFunctions();
  Advance();
}

void Parser::RegisterParseFunctions() {
  // literals
  prefix_parsers_[TokenType::IDENTIFIER]         = IdentifierParseFn;
  prefix_parsers_[TokenType::NIL]                = NilParseFn;
  prefix_parsers_[TokenType::NUMBER]             = NumberParseFn;
  prefix_parsers_[TokenType::STRING]             = StringParseFn;
  prefix_parsers_[TokenType::LEFT_PAREN]         = GroupingParseFn;
  prefix_parsers_[TokenType::TRUE]               = BooleanParseFn;
  prefix_parsers_[TokenType::FALSE]              = BooleanParseFn;

  // arithmetic
  infix_parsers_[TokenType::PLUS]                = AdditionParseFn;
  infix_parsers_[TokenType::MINUS]               = SubtractionParseFn;
  infix_parsers_[TokenType::STAR]                = MultiplicationParseFn;
  infix_parsers_[TokenType::SLASH]               = DivisionParseFn;

  // comparison
  infix_parsers_[TokenType::EQUALS]              = EqualsParseFn;
  infix_parsers_[TokenType::UNEQUAL]             = UnequalParseFn;
  infix_parsers_[TokenType::GREATER_OR_EQUAL_TO] = GreaterOrEqualToParseFn;
  infix_parsers_[TokenType::LESS_OR_EQUAL_TO]    = LessOrEqualToParseFn;
  infix_parsers_[TokenType::LESS_THAN]           = LessThanParseFn;
  infix_parsers_[TokenType::GREATER_THAN]        = GreaterThanParseFn;
  infix_parsers_[TokenType::OR]                  = OrParseFn;
  infix_parsers_[TokenType::AND]                 = AndParseFn;
  infix_parsers_[TokenType::LEFT_PAREN]          = FunctionCallParseFn;

  // assignment
  infix_parsers_[TokenType::ASSIGN]              = AssignmentParseFn;

  // statements
  statement_parsers_[TokenType::VAR]             = VarParseFn;
  statement_parsers_[TokenType::PRINT]           = PrintParseFn;
  statement_parsers_[TokenType::LEFT_BRACE]      = BlockParseFn;
  statement_parsers_[TokenType::IF]              = IfParseFn;
  statement_parsers_[TokenType::WHILE]           = WhileParseFn;
  statement_parsers_[TokenType::FOR]             = ForParseFn;
  statement_parsers_[TokenType::SEMICOLON]       = EmptyStatementParseFn;
  statement_parsers_[TokenType::FUN]             = FunctionDeclarationParseFn;
  statement_parsers_[TokenType::RETURN]          = ReturnStatementParseFn;
  statement_parsers_[TokenType::CLASS]           = ClassDeclarationParseFn;

  // unaries
  prefix_parsers_[TokenType::MINUS]              = UnaryMinusParseFn;
  prefix_parsers_[TokenType::BANG]               = LogicalNotParseFn;

  // access
  infix_parsers_[TokenType::DOT]                 = DotOperatorParseFn;
  prefix_parsers_[TokenType::THIS]               = ThisOperatorParseFn;
  prefix_parsers_[TokenType::SUPER]              = SuperParseFn;
}

void Parser::Advance() { current_ = lex_.NextToken(); }

bool Parser::Consume(const TokenType type) {
  if (current_.type == type) {
    Advance();
    return true;
  }

  errors_.emplace_back("[line " + std::to_string(lex_.line()) + "] Error at '" +
                           current_.value + "': Expect expression",
                       current_.line, current_.column);

  // Tries fast-forwarding to some landmark
  while (current_.type != TokenType::END_OF_FILE &&
         current_.type != TokenType::SEMICOLON) {
    Advance();
  }

  return false;
}

ast::expr::Expression Parser::ParseExpression(const int32_t min_bp) {
  const Token tok = current_;
  Advance();

  const auto prefix_it = prefix_parsers_.find(tok.type);
  if (prefix_it == prefix_parsers_.end()) {
    ReportError(tok);
    return ast::expr::Nil(tok);
  }

  auto left = prefix_it->second(*this, tok);

  while (true) {
    auto infix_it = infix_parsers_.find(current_.type);
    if (infix_it == infix_parsers_.end())
      break;

    auto [lbp, rbp] = infix_binding_power(current_.type);
    if (lbp < min_bp)
      break;

    const auto op_tok = current_;
    Advance();

    const auto left_ptr = std::make_shared<ast::expr::Expression>(std::move(left));
    left = infix_it->second(*this, op_tok, left_ptr);
  }

  return left;
}

ast::stmt::Statement Parser::ParseStatement() {
  const Token tok = current_;
  const auto statement_parse_it = statement_parsers_.find(current_.type);
  if (statement_parse_it == statement_parsers_.end()) {
    auto expr = ParseExpression(0);
    const auto expr_ptr = std::make_shared<ast::expr::Expression>(expr);
    Consume(TokenType::SEMICOLON);
    return ast::stmt::ExpressionStatement(tok, expr_ptr);
  }

  Advance();
  return statement_parse_it->second(*this, tok);
}

ast::stmt::Program Parser::ParseProgram() {
  std::vector<std::shared_ptr<ast::stmt::Statement>> statements;
  while (current_.type != TokenType::END_OF_FILE) {
    statements.push_back(
        std::make_shared<ast::stmt::Statement>(ParseStatement()));
  }

  return ast::stmt::Program{statements};
}

void Parser::ReportError(const Token &tok) {
  errors_.emplace_back("[line " + std::to_string(tok.line) + "] Error at '" +
                       tok.value + "': Expect expression",
                       tok.line, tok.column);
}
std::vector<ParserError> Parser::errors() const { return errors_; }
} // namespace lox::parser