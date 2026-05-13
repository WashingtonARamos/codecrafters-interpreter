#include "../../../inc/analysis/visitors/identifier_finder_visitor.h"
#include "../../../inc/analysis/visitors/identifier_resolution_visitor.h"
#include "../../../inc/analysis/contexts/identifier_resolution_context.h"

#include <algorithm>
#include <vector>

namespace lox::analysis::visitors {

using namespace lox::analysis::contexts;
using namespace lox::ast::stmt;
using namespace lox::ast::expr;
using namespace lox::interpreter;

bool ReadsName(const std::string &name, const Expression &expr) {
  const auto finder_ctx = std::make_shared<IdentifierFinderContext>();
  IdentifierFinderVisitor visitor;
  visitor.Visit(expr, finder_ctx);

  return std::ranges::any_of(finder_ctx->identifiers, [&](const auto &identifier) {
    return identifier == name;
  });
}

void IdentifierResolutionVisitor::Visit(
    const Assignment &expr,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (expr.value)
    Visit(*expr.value, ctx);
  if (expr.target) {
    if (const auto *id = std::get_if<Identifier>(&*expr.target))
      ctx->ResolveLocal(id);
  }
}

void IdentifierResolutionVisitor::Visit(
    const Block &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (ctx->bypass_block_creation) {
    ctx->bypass_block_creation = false;
    for (const auto &stmt_child : stmt.statements) {
      if (stmt_child)
        Visit(*stmt_child, ctx);
    }
    return;
  }

  ctx->BeginScope();
  for (const auto &stmt_child : stmt.statements) {
    if (stmt_child)
      Visit(*stmt_child, ctx);
  }
  ctx->EndScope();
}

void IdentifierResolutionVisitor::Visit(
    const For &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  ctx->BeginScope();
  if (stmt.initializer)
    Visit(*stmt.initializer, ctx);
  ctx->BeginScope();
  if (stmt.condition)
    Visit(*stmt.condition, ctx);
  if (stmt.increment)
    Visit(*stmt.increment, ctx);
  if (std::holds_alternative<Block>(*stmt.body))
    ctx->bypass_block_creation = true;
  Visit(*stmt.body, ctx);
  ctx->EndScope();
  ctx->EndScope();
}

void IdentifierResolutionVisitor::Visit(
    const Identifier &identifier,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (identifier.name == "this") {
    if (!ctx->inside_class)
      ctx->errors.emplace_back("Can't use 'this' outside of a class",
                               identifier);
  } else if (identifier.name == "super") {
    if (!ctx->inside_class)
      ctx->errors.emplace_back("Can't use 'super' outside of a class",
                               identifier);
    if (!ctx->inside_subclass)
      ctx->errors.emplace_back(
          "Can't use 'super' in a class with no superclass", identifier);
  } else {
    ctx->ResolveLocal(&identifier);
  }
}

void IdentifierResolutionVisitor::Visit(
    const VariableDeclaration &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (ctx->scopes.size() > 1 && stmt.initializer) {
    if (ReadsName(stmt.name->name, *stmt.initializer)) {
      ctx->errors.emplace_back("Variable declaration cannot read its own name",
                               *stmt.initializer);
      return;
    }
  }

  if (stmt.initializer)
    Visit(*stmt.initializer, ctx);

  ctx->Declare(*stmt.name);
}

void IdentifierResolutionVisitor::Visit(
    const Return &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (!ctx->inside_function) {
    ctx->errors.emplace_back("Can only return from inside functions", stmt);
    return;
  }

  if (ctx->inside_constructor && stmt.value) {
    ctx->errors.emplace_back("Can't return from inside a constructor", stmt);
    return;
  }

  if (stmt.value)
    Visit(*stmt.value, ctx);
}

void IdentifierResolutionVisitor::Visit(
    const ClassDeclaration &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (stmt.superclass) {
    if (stmt.name->name == stmt.superclass->name) {
      ctx->errors.emplace_back("A class can't inherit from itself", stmt);
    }
    ctx->inside_subclass = true;
  }
  const bool was_inside_class = ctx->inside_class;
  ctx->inside_class = true;
  ctx->Declare(*stmt.name);
  ctx->BeginScope();
  for (const auto &method : stmt.methods) {
    Visit(*method, ctx);
  }
  ctx->EndScope();
  ctx->inside_class = was_inside_class;
  ctx->inside_subclass = false;
}

void IdentifierResolutionVisitor::Visit(
    const FunctionDeclaration &stmt,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  const bool was_inside_function = ctx->inside_function;
  ctx->inside_function = true;
  if (stmt.name->name == "init" && ctx->inside_class) {
    ctx->inside_constructor = true;
  }
  ctx->Declare(*stmt.name);
  ctx->BeginScope();

  for (const auto &arg : stmt.arguments) {
    ctx->Declare(*arg);
  }

  ctx->bypass_block_creation = true;
  if (stmt.body)
    Visit(*stmt.body, ctx);

  ctx->inside_constructor = false;
  ctx->inside_function = was_inside_function;
  ctx->EndScope();
}

void IdentifierResolutionVisitor::Visit(
    const FunctionCall &expr,
    const std::shared_ptr<IdentifierResolutionContext> &ctx) {
  if (std::holds_alternative<Identifier>(*expr.callee)) {
    ctx->ResolveLocal(&std::get<Identifier>(*expr.callee));
  } else {
    Visit(*expr.callee, ctx);
  }
  for (const auto &arg : expr.arguments)
    Visit(*arg, ctx);
}

} // namespace lox::analysis::visitors