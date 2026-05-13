#ifndef CODECRAFTERS_INTERPRETER_FUNCTION_PARSE_H
#define CODECRAFTERS_INTERPRETER_FUNCTION_PARSE_H
#include "../parse_function.h"

namespace lox::parser {

ast::stmt::Statement FunctionDeclarationParseFn(Parser &parser,
                                                 const lexer::Token &token);
ast::expr::Expression
FunctionCallParseFn(Parser &parser, const lexer::Token &token,
                    const std::shared_ptr<ast::expr::Expression> &left);

} // namespace lox::parser

#endif
