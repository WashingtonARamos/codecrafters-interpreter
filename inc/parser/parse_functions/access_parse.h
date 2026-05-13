#ifndef CODECRAFTERS_INTERPRETER_ACCESS_PARSE_H
#define CODECRAFTERS_INTERPRETER_ACCESS_PARSE_H
#include "../parse_function.h"

#include <memory>

namespace lox::parser {

ast::expr::Expression
DotOperatorParseFn(Parser &parser, const lexer::Token &token,
                   const std::shared_ptr<ast::expr::Expression> &left);

ast::expr::Expression ThisOperatorParseFn(Parser &parser,
                                          const lexer::Token &token);
ast::expr::Expression SuperParseFn(Parser &parser,
                                          const lexer::Token &token);

}

#endif
