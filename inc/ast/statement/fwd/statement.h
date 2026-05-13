#ifndef CODECRAFTERS_INTERPRETER_FWD_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_FWD_STATEMENT_H
#include "block.h"
#include "class_declaration.h"
#include "empty_statement.h"
#include "expression_statement.h"
#include "for.h"
#include "function_declaration.h"
#include "if_statement.h"
#include "print_statement.h"
#include "return.h"
#include "variable_declaration.h"
#include "while.h"

#include "program.h"

#include <cstdint>
#include <variant>

namespace lox::ast::stmt {

using Statement =
    std::variant<Block, ClassDeclaration, EmptyStatement, ExpressionStatement, For,
                 FunctionDeclaration, IfStatement, PrintStatement, Program,
                 Return, VariableDeclaration, While>;
} // namespace lox::ast::stmt

#endif
