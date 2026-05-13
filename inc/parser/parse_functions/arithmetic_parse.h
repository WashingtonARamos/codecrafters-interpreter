#ifndef CODECRAFTERS_INTERPRETER_BINARY_PARSELET_H
#define CODECRAFTERS_INTERPRETER_BINARY_PARSELET_H
#include "../parse_function.h"

#include <memory>

namespace lox::parser {

ast::expr::Expression
AdditionParseFn(Parser &parser, const lexer::Token &token,
                const std::shared_ptr<ast::expr::Expression> &left);
ast::expr::Expression
DivisionParseFn(Parser &parser, const lexer::Token &token,
                const std::shared_ptr<ast::expr::Expression> &left);
ast::expr::Expression
MultiplicationParseFn(Parser &parser, const lexer::Token &token,
                      const std::shared_ptr<ast::expr::Expression> &left);
ast::expr::Expression
SubtractionParseFn(Parser &parser, const lexer::Token &token,
                   const std::shared_ptr<ast::expr::Expression> &left);

} // namespace lox::parser

#endif