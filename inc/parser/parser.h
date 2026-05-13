#ifndef CODECRAFTERS_INTERPRETER_PARSER_H
#define CODECRAFTERS_INTERPRETER_PARSER_H
#include "../ast/expression/fwd/expr.h"
#include "../ast/statement/fwd/statement.h"
#include "../lexer/lexer.h"
#include "parse_function.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace lox::parser {
struct ParserError {
  std::string message;
  int32_t line;
  int32_t column{0};
};

class Parser {
  lexer::Lexer lex_;
  lexer::Token current_;
  std::vector<ParserError> errors_;

  std::unordered_map<lexer::TokenType, PrefixParser> prefix_parsers_;
  std::unordered_map<lexer::TokenType, InfixParser> infix_parsers_;
  std::unordered_map<lexer::TokenType, StatementParser> statement_parsers_;

  void RegisterParseFunctions();


public:
  explicit Parser(const lexer::Lexer &lexer);
  ast::expr::Expression ParseExpression(int32_t min_bp);
  ast::stmt::Statement ParseStatement();
  void Advance();
  bool Consume(lexer::TokenType type);
  // Allows parsers to report back to the parser
  void ReportError(const lexer::Token & tok);
  lexer::Token CurrentToken() const { return current_; }
  lexer::Token PeekNext() const { return lex_.PeekNext(); }

  ast::stmt::Program ParseProgram();
  [[nodiscard]] std::vector<ParserError> errors() const;
};
} // namespace lox::parser

#endif
