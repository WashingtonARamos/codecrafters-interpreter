#ifndef CODECRAFTERS_INTERPRETER_ASSIGNMENT_PARSE_H
#define CODECRAFTERS_INTERPRETER_ASSIGNMENT_PARSE_H
#include "../parse_function.h"

namespace lox::parser {
ast::expr::Expression
AssignmentParseFn(Parser &parser, const lexer::Token &token,
                  const std::shared_ptr<ast::expr::Expression> &left);
}

#endif
