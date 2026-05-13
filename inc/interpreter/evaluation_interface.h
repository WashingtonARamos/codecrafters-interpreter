#ifndef CODECRAFTERS_INTERPRETER_EVALUATION_INTERFACE_H
#define CODECRAFTERS_INTERPRETER_EVALUATION_INTERFACE_H
#include "../ast/expression/fwd/expr.h"
#include "../ast/statement/fwd/statement.h"

#include "lox_value.h"

namespace lox::interpreter {
struct Context;

// Base
LoxValue Evaluate(const ast::expr::Expression &expr);
LoxValue Evaluate(const ast::expr::Expression &expr,
                  const std::shared_ptr<Context> &ctx);
// Root for program execution
std::shared_ptr<LoxValue> Execute(const ast::stmt::Program &stmt);
std::shared_ptr<LoxValue> Execute(const ast::stmt::Statement &stmt,
                                  const std::shared_ptr<Context> &ctx);

// Leaves
LoxValue Evaluate(const ast::expr::Boolean &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Number &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::LoxString &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Nil &expr,
                  const std::shared_ptr<Context> &ctx);

// Binaries
LoxValue Evaluate(const ast::expr::Addition &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Assignment &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Division &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Multiplication &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Subtraction &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Equality &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Inequality &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::GreaterOrEqualTo &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::LessOrEqualTo &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::GreaterThan &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::LessThan &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::And &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Or &expr,
                  const std::shared_ptr<Context> &ctx);

// Function
LoxValue Evaluate(const ast::expr::FunctionCall &expr,
                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::FunctionDeclaration &expr,
                                  const std::shared_ptr<Context> &ctx);

// Unaries
LoxValue Evaluate(const ast::expr::UnaryMinus &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::LogicalNot &expr,
                  const std::shared_ptr<Context> &ctx);

// Misc
LoxValue Evaluate(const ast::expr::Grouping &expr,
                  const std::shared_ptr<Context> &ctx);
LoxValue Evaluate(const ast::expr::Identifier &expr,
                  const std::shared_ptr<Context> &ctx);

// Statements
std::shared_ptr<LoxValue> Execute(const ast::stmt::Block &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::ExpressionStatement &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::PrintStatement &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::VariableDeclaration &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::IfStatement &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::For &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::While &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::EmptyStatement &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::Return &stmt,
                                  const std::shared_ptr<Context> &ctx);
std::shared_ptr<LoxValue> Execute(const ast::stmt::ClassDeclaration &stmt,
                                  const std::shared_ptr<Context> &ctx);

// Access
LoxValue Evaluate(const ast::expr::DotOperator &expr,
                  const std::shared_ptr<Context> &ctx);

std::string ToString(const LoxValue &value);

} // namespace lox::interpreter

#endif
