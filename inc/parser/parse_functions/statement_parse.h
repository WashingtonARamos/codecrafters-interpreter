#ifndef CODECRAFTERS_INTERPRETER_STATEMENT_PARSE_H
#define CODECRAFTERS_INTERPRETER_STATEMENT_PARSE_H
#include "../parse_function.h"

namespace lox::parser {

ast::stmt::Statement BlockParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement ClassDeclarationParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement EmptyStatementParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement IfParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement PrintParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement ReturnStatementParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement VarParseFn(Parser &parser, const lexer::Token &token);

// Loops
ast::stmt::Statement ForParseFn(Parser &parser, const lexer::Token &token);
ast::stmt::Statement WhileParseFn(Parser &parser, const lexer::Token &token);

}

#endif
