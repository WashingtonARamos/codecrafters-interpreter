#ifndef CODECRAFTERS_INTERPRETER_TREE_ANALYSIS_H
#define CODECRAFTERS_INTERPRETER_TREE_ANALYSIS_H
#include "../ast/statement/fwd/statement.h"
#include "contexts/identifier_resolution_context.h"

namespace lox::analysis {

contexts::IdentifierResolutionContext
ResolveVariables(const ast::stmt::Statement &stmt);
}

#endif
