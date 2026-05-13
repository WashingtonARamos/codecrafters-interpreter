#ifndef CODECRAFTERS_INTERPRETER_IDENTIFIER_RESOLUTION_VISITOR_H
#define CODECRAFTERS_INTERPRETER_IDENTIFIER_RESOLUTION_VISITOR_H
#include "../contexts/identifier_resolution_context.h"
#include "generic_visitor.h"

namespace lox::analysis::visitors {

struct IdentifierResolutionVisitor
    : GenericVisitor<
          IdentifierResolutionVisitor,
          const std::shared_ptr<contexts::IdentifierResolutionContext> &> {

  using GenericVisitor::Visit;

  void Visit(const ast::expr::Assignment &expr,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::Block &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::For &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::expr::Identifier &identifier,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::FunctionDeclaration &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::VariableDeclaration &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::expr::FunctionCall &expr,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::Return &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
  void Visit(const ast::stmt::ClassDeclaration &stmt,
             const std::shared_ptr<contexts::IdentifierResolutionContext> &ctx);
};

} // namespace lox::analysis::visitors

#endif