#ifndef CODECRAFTERS_INTERPRETER_FWD_EXPRESSION_H
#define CODECRAFTERS_INTERPRETER_FWD_EXPRESSION_H
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

#include <variant>

namespace lox::ast::expr {
using Expression =
    std::variant<Boolean, DotOperator, LoxString, Number, Nil, Assignment,
                 Addition, Division, Multiplication, Subtraction, UnaryMinus,
                 Grouping, LogicalNot, Equality, Inequality, GreaterOrEqualTo,
                 LessOrEqualTo, GreaterThan, LessThan, Identifier, Or, And,
                 FunctionCall>;

using BinaryExpression =
    std::variant<Addition, Subtraction, Multiplication, Division, Equality,
                 Inequality, GreaterOrEqualTo, LessOrEqualTo, GreaterThan,
                 LessThan, Or, And>;

using UnaryExpression = std::variant<UnaryMinus, LogicalNot>;

using ValueExpression =
    std::variant<Boolean, LoxString, Number, Nil, Assignment>;
} // namespace lox::ast::expr

#endif
