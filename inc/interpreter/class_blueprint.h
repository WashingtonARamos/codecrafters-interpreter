#ifndef CODECRAFTERS_INTERPRETER_CLASS_BLUEPRINT_H
#define CODECRAFTERS_INTERPRETER_CLASS_BLUEPRINT_H
#include "fwd/lox_value.h"

#include <string>

namespace lox::interpreter {
struct Context;
// In Lox, classes can be called upon like functions, passed around like values
// and printed like variables, so when a class is declared, we add a
// ClassBlueprint to the environment, and this object becomes the class
struct ClassBlueprint {
  ClassBlueprint(std::string name, std::shared_ptr<ClassBlueprint> superclass, std::shared_ptr<Context> context,
                 std::vector<std::shared_ptr<ast::stmt::FunctionDeclaration>> methods)
      : name(std::move(name)), context(std::move(context)),
        methods(std::move(methods)), superclass(std::move(superclass)) {}

  std::string name;
  std::shared_ptr<Context> context;
  std::vector<std::shared_ptr<ast::stmt::FunctionDeclaration>> methods;
  std::shared_ptr<ClassBlueprint> superclass;
};
} // namespace lox::interpreter

#endif