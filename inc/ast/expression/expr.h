#ifndef CODECRAFTERS_INTERPRETER_EXPRESSION_H
#define CODECRAFTERS_INTERPRETER_EXPRESSION_H
#include "addition.h"
#include "and.h"
#include "assignment.h"
#include "boolean.h"
#include "division.h"
#include "dot_operator.h"
#include "equality.h"
#include "function_call.h"
#include "greater_or_equal_to.h"
#include "greater_than.h"
#include "grouping.h"
#include "identifier.h"
#include "inequality.h"
#include "less_or_equal_to.h"
#include "less_than.h"
#include "logical_not.h"
#include "lox_string.h"
#include "multiplication.h"
#include "nil.h"
#include "number.h"
#include "or.h"
#include "subtraction.h"
#include "unary_minus.h"

#include "../../util/variant_utils.h"

#include <format>
#include <string>
#include <variant>

namespace lox::ast::expr {

template <class T>
static constexpr bool is_binary_op = is_alternative<T, BinaryExpression>::value;

template <class T>
static constexpr bool is_unary_op = is_alternative<T, UnaryExpression>::value;

template <class T>
static constexpr bool holds_value = is_alternative<T, ValueExpression>::value;

template <class T> constexpr std::string get_op_symbol() {
  static_assert(is_binary_op<T> || is_unary_op<T>);
  using U = std::decay_t<T>;

  if constexpr (std::is_same_v<U, Addition>)
    return "+";
  else if constexpr (std::is_same_v<U, Multiplication>)
    return "*";
  else if constexpr (std::is_same_v<U, Division>)
    return "/";
  else if constexpr (std::is_same_v<U, LogicalNot>)
    return "!";
  else if constexpr (std::is_same_v<U, UnaryMinus> ||
                     std::is_same_v<U, Subtraction>)
    return "-";
  else if constexpr (std::is_same_v<U, Equality>)
    return "==";
  else if constexpr (std::is_same_v<U, Inequality>)
    return "!=";
  else if constexpr (std::is_same_v<U, GreaterOrEqualTo>)
    return ">=";
  else if constexpr (std::is_same_v<U, LessOrEqualTo>)
    return "<=";
  else if constexpr (std::is_same_v<U, GreaterThan>)
    return ">";
  else if constexpr (std::is_same_v<U, LessThan>)
    return "<";
  else if constexpr (std::is_same_v<U, Or>)
    return "OR";
  else if constexpr (std::is_same_v<U, And>)
    return "AND";
  else
    return "unknown";
}

template <class T> constexpr std::string get_value(T node) {
  static_assert(holds_value<T>);
  using U = std::decay_t<T>;

  if constexpr (std::is_same_v<U, Nil>)
    return "nil";
  else if constexpr (std::is_same_v<U, Number>) {
    std::string formatted = std::format("{}", node.value);
    if (formatted.find('.') == std::string::npos)
      formatted += ".0";
    return formatted;
  } else if constexpr (std::is_same_v<U, Boolean>)
    return node.value ? "true" : "false";
  else if constexpr (std::is_same_v<U, LoxString>)
    return node.value;
  else if constexpr (std::is_same_v<U, Identifier>)
    return node.name;

  return "unknown";
}

constexpr uint32_t get_line(Expression node) {
  return std::visit([](auto &&expr) -> uint32_t {
    return expr.line;
  }, node);
}

} // namespace lox::ast::expr

#endif
