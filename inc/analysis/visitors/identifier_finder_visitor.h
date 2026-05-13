#ifndef CODECRAFTERS_INTERPRETER_IDENTIFIER_FINDER_VISITOR_H
#define CODECRAFTERS_INTERPRETER_IDENTIFIER_FINDER_VISITOR_H
#include "../contexts/identifier_finder_context.h"
#include "generic_visitor.h"

namespace lox::analysis::visitors {
struct IdentifierFinderVisitor
    : GenericVisitor<
          IdentifierFinderVisitor,
          const std::shared_ptr<contexts::IdentifierFinderContext> &> {
  using GenericVisitor::Visit;

  static void Visit(const ast::expr::Identifier &expr,
             const std::shared_ptr<contexts::IdentifierFinderContext> &ctx);
};
}

#endif
