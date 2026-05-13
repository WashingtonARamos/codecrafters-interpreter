#ifndef CODECRAFTERS_INTERPRETER_UNARY_PARSELET_H
#define CODECRAFTERS_INTERPRETER_UNARY_PARSELET_H
#include "../parse_function.h"

namespace lox::parser {

ast::expr::Expression LogicalNotParseFn(Parser &parser, const lexer::Token &token);
ast::expr::Expression UnaryMinusParseFn(Parser &parser, const lexer::Token &token);

} // namespace lox::parser

#endif