#ifndef CODECRAFTERS_INTERPRETER_GENERIC_VISITOR_H
#define CODECRAFTERS_INTERPRETER_GENERIC_VISITOR_H
#include "../../ast/expression/expr.h"
#include "../../ast/statement/statement.h"

namespace lox::analysis::visitors {

template <typename Derived, typename Context> struct GenericVisitor {

  /*
  // Statements
  */
  void Visit(const ast::stmt::Statement &stmt, Context ctx) {
    std::visit(
        [this, &ctx](const auto &node) -> void {
          static_cast<Derived *>(this)->Visit(node, ctx);
        },
        stmt);
  }

  void Visit(const ast::stmt::Block &stmt, Context ctx) {
    for (const auto &child_stmt : stmt.statements)
      if (child_stmt)
        static_cast<Derived *>(this)->Visit(child_stmt, ctx);
  }

  void Visit(const ast::stmt::ClassDeclaration &stmt, Context ctx) {
    if (stmt.name)
      static_cast<Derived *>(this)->Visit(*stmt.name, ctx);
    for (const auto &method : stmt.methods)
      if (method)
        static_cast<Derived *>(this)->Visit(*method, ctx);
  }

  void Visit(const ast::stmt::EmptyStatement & /*stmt*/, Context & /*ctx*/) {
    // no-op
  }

  void Visit(const ast::stmt::ExpressionStatement &stmt, Context ctx) {
    if (stmt.expression)
      static_cast<Derived *>(this)->Visit(*stmt.expression, ctx);
  }

  void Visit(const ast::stmt::For &stmt, Context ctx) {
    if (stmt.initializer)
      static_cast<Derived *>(this)->Visit(*stmt.initializer, ctx);
    if (stmt.condition)
      static_cast<Derived *>(this)->Visit(*stmt.condition, ctx);
    if (stmt.increment)
      static_cast<Derived *>(this)->Visit(*stmt.increment, ctx);
    if (stmt.body)
      static_cast<Derived *>(this)->Visit(*stmt.body, ctx);
  }

  void Visit(const ast::stmt::FunctionDeclaration &stmt, Context ctx) {
    if (stmt.name)
      static_cast<Derived *>(this)->Visit(*stmt.name, ctx);
    for (const auto &arg : stmt.arguments)
      if (arg)
        static_cast<Derived *>(this)->Visit(*arg, ctx);
    if (stmt.body)
      static_cast<Derived *>(this)->Visit(*stmt.body, ctx);
  }

  void Visit(const ast::stmt::IfStatement &stmt, Context ctx) {
    if (stmt.condition)
      static_cast<Derived *>(this)->Visit(*stmt.condition, ctx);
    if (stmt.if_stmt)
      static_cast<Derived *>(this)->Visit(*stmt.if_stmt, ctx);
    if (stmt.else_stmt)
      static_cast<Derived *>(this)->Visit(*stmt.else_stmt, ctx);
  }

  void Visit(const ast::stmt::PrintStatement &stmt, Context ctx) {
    if (stmt.expression)
      static_cast<Derived *>(this)->Visit(*stmt.expression, ctx);
  }

  void Visit(const ast::stmt::Program &stmt, Context ctx) {
    for (const auto &child_stmt : stmt.statements)
      if (child_stmt)
        static_cast<Derived *>(this)->Visit(*child_stmt, ctx);
  }

  void Visit(const ast::stmt::Return &stmt, Context ctx) {
    if (stmt.value)
      static_cast<Derived *>(this)->Visit(*stmt.value, ctx);
  }

  void Visit(const ast::stmt::VariableDeclaration &stmt, Context ctx) {
    if (stmt.name)
      static_cast<Derived *>(this)->Visit(*stmt.name, ctx);
    if (stmt.initializer)
      static_cast<Derived *>(this)->Visit(*stmt.initializer, ctx);
  }

  void Visit(const ast::stmt::While &stmt, Context ctx) {
    if (stmt.condition)
      static_cast<Derived *>(this)->Visit(*stmt.condition, ctx);
    if (stmt.body)
      static_cast<Derived *>(this)->Visit(*stmt.body, ctx);
  }

  /*
  // Expressions
  */
  void Visit(const ast::expr::Expression &expr, Context ctx) {
    std::visit(
        [this, &ctx](const auto &node) -> void {
          static_cast<Derived *>(this)->Visit(node, ctx);
        },
        expr);
  }

  void Visit(const ast::expr::Addition &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::DotOperator &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::And &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Assignment &expr, Context ctx) {
    if (expr.value)
      static_cast<Derived *>(this)->Visit(*expr.value, ctx);
    if (expr.target)
      static_cast<Derived *>(this)->Visit(*expr.target, ctx);
  }

  void Visit(const ast::expr::Division &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Equality &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::FunctionCall &expr, Context ctx) {
    if (expr.callee)
      static_cast<Derived *>(this)->Visit(*expr.callee, ctx);
    for (const auto &arg : expr.arguments)
      static_cast<Derived *>(this)->Visit(*arg, ctx);
  }

  void Visit(const ast::expr::GreaterOrEqualTo &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::GreaterThan &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Grouping &expr, Context ctx) {
    if (expr.expression)
      static_cast<Derived *>(this)->Visit(*expr.expression, ctx);
  }

  void Visit(const ast::expr::Inequality &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::LessOrEqualTo &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::LessThan &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::LogicalNot &expr, Context ctx) {
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Multiplication &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Or &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Subtraction &expr, Context ctx) {
    if (expr.left)
      static_cast<Derived *>(this)->Visit(*expr.left, ctx);
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::UnaryMinus &expr, Context ctx) {
    if (expr.right)
      static_cast<Derived *>(this)->Visit(*expr.right, ctx);
  }

  void Visit(const ast::expr::Boolean & /*expr*/, Context /*ctx*/) {
    // Leaf
  }

  void Visit(const ast::expr::Identifier & /*expr*/, Context /*ctx*/) {
    // Leaf
  }

  void Visit(const ast::expr::LoxString & /*expr*/, Context /*ctx*/) {
    // Leaf
  }

  void Visit(const ast::expr::Nil & /*expr*/, Context /*ctx*/) {
    // Leaf
  }

  void Visit(const ast::expr::Number & /*expr*/, Context /*ctx*/) {
    // Leaf
  }
};

} // namespace lox::analysis::visitors

#endif