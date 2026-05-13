#ifndef CODECRAFTERS_INTERPRETER_STATEMENT_H
#define CODECRAFTERS_INTERPRETER_STATEMENT_H
#include "block.h"
#include "class_declaration.h"
#include "empty_statement.h"
#include "expression_statement.h"
#include "for.h"
#include "function_declaration.h"
#include "if_statement.h"
#include "print_statement.h"
#include "program.h"
#include "return.h"
#include "variable_declaration.h"
#include "while.h"

#include "../../util/variant_utils.h"

namespace lox::ast::stmt {

constexpr uint32_t get_line(Statement node) {
  return std::visit([](auto &&stmt) -> uint32_t { return stmt.line; }, node);
}

} // namespace lox::ast::stmt

#endif
