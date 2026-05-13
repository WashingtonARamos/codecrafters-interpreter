#ifndef CODECRAFTERS_INTERPRETER_ASTPRINTER_H
#define CODECRAFTERS_INTERPRETER_ASTPRINTER_H
#include "../ast/expression/expr.h"
#include <format>
#include <iostream>
#include <string>

namespace lox::util {
inline std::string PrintAst(const ast::expr::Expression &expr) {

  return std::visit(
      []<typename T>(T &&val) -> std::string {
        if constexpr (ast::expr::holds_value<T>) {
          return ast::expr::get_value<T>(val);
        } else if constexpr (std::is_same_v<T, ast::expr::Grouping>) {
          return "(group " + PrintAst(*val.expression) + ")";
        } else if constexpr (ast::expr::is_binary_op<T>) {
          return "(" + ast::expr::get_op_symbol<T>() + " " + PrintAst(*val.left) +
                 " " + PrintAst(*val.right) + ")";
        } else if constexpr (ast::expr::is_unary_op<T>) {
          return "(" + ast::expr::get_op_symbol<T>() + " " + PrintAst(*val.right) + ")";
        } else {
          throw std::runtime_error("Unknown expression type");
        }
      },
      expr);
}
} // namespace lox::util

#endif
