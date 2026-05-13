#include "../../inc/analysis/visitors/identifier_resolution_visitor.h"
#include "../../inc/analysis/tree_analysis.h"

#include <memory>

namespace lox::analysis {

using namespace ast::expr;
using namespace lox::analysis::contexts;
using namespace lox::analysis::visitors;
using namespace lox::interpreter;

IdentifierResolutionContext
ResolveVariables(const ast::stmt::Statement &stmt) {
  const auto context = std::make_shared<IdentifierResolutionContext>();
  IdentifierResolutionVisitor visitor;

  context->BeginScope();
  visitor.Visit(stmt, context);

  return *context;
}


} // namespace lox::analysis
