#ifndef CODECRAFTERS_INTERPRETER_IDENTIFIER_FINDER_CONTEXT_H
#define CODECRAFTERS_INTERPRETER_IDENTIFIER_FINDER_CONTEXT_H
#include <string>
#include <vector>

namespace lox::analysis::contexts {

struct IdentifierFinderContext {
  std::vector<std::string> identifiers;
};

} // namespace lox::analysis::contexts

#endif