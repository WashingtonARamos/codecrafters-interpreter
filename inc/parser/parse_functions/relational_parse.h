#ifndef CODECRAFTERS_INTERPRETER_LOGICAL_PARSE_H
#define CODECRAFTERS_INTERPRETER_LOGICAL_PARSE_H
#include "../parse_function.h"

namespace lox::parser {

// ==
ast::expr::Expression
EqualsParseFn(Parser &parser, const lexer::Token &token,
              const std::shared_ptr<ast::expr::Expression> &left);

// !=
ast::expr::Expression
UnequalParseFn(Parser &parser, const lexer::Token &token,
               const std::shared_ptr<ast::expr::Expression> &left);

// >
ast::expr::Expression
GreaterThanParseFn(Parser &parser, const lexer::Token &token,
                   const std::shared_ptr<ast::expr::Expression> &left);

// >=
ast::expr::Expression
GreaterOrEqualToParseFn(Parser &parser, const lexer::Token &token,
                        const std::shared_ptr<ast::expr::Expression> &left);

// <
ast::expr::Expression
LessThanParseFn(Parser &parser, const lexer::Token &token,
                const std::shared_ptr<ast::expr::Expression> &left);

// <=
ast::expr::Expression
LessOrEqualToParseFn(Parser &parser, const lexer::Token &token,
                     const std::shared_ptr<ast::expr::Expression> &left);

// OR
ast::expr::Expression
OrParseFn(Parser &parser, const lexer::Token &token,
          const std::shared_ptr<ast::expr::Expression> &left);

// AND
ast::expr::Expression
AndParseFn(Parser &parser, const lexer::Token &token,
          const std::shared_ptr<ast::expr::Expression> &left);

} // namespace lox::parser

#endif