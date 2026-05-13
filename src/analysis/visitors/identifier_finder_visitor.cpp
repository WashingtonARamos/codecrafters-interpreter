#include "../../../inc/analysis/visitors/identifier_finder_visitor.h"
#include "../../../inc/analysis/contexts/identifier_finder_context.h"
#include <vector>

namespace lox::analysis::visitors {

using namespace lox::analysis::contexts;
using namespace lox::ast::stmt;
using namespace lox::ast::expr;

void IdentifierFinderVisitor::Visit(
    const Identifier &expr,
    const std::shared_ptr<IdentifierFinderContext> &ctx) {
  ctx->identifiers.push_back(expr.name);
}
} // namespace lox::analysis::visitors