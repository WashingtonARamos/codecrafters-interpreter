#ifndef CODECRAFTERS_INTERPRETER_LITERAL_PARSELET_H
#define CODECRAFTERS_INTERPRETER_LITERAL_PARSELET_H
#include "../parse_function.h"

namespace lox::parser {

ast::expr::Expression BooleanParseFn(Parser &parser, const lexer::Token &token);
ast::expr::Expression GroupingParseFn(Parser &parser,
                                      const lexer::Token &token);
ast::expr::Expression IdentifierParseFn(Parser &parser,
                                        const lexer::Token &token);
ast::expr::Expression NilParseFn(Parser &parser, const lexer::Token &token);
ast::expr::Expression NumberParseFn(Parser &parser, const lexer::Token &token);
ast::expr::Expression StringParseFn(Parser &parser, const lexer::Token &token);

} // namespace lox::parser

#endif