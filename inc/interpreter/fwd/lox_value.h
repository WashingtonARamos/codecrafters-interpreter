#ifndef CODECRAFTERS_INTERPRETER_FWD_LOX_VALUE_H
#define CODECRAFTERS_INTERPRETER_FWD_LOX_VALUE_H
#include "class_blueprint.h"
#include "class_instance.h"
#include "interpreter_error.h"
#include "lox_function.h"

#include <string>
#include <variant>

namespace lox::interpreter {
using LoxValue = std::variant<std::monostate, double, bool, std::string, LoxFunction,
                              InterpreterError, ClassInstance, ClassBlueprint>;
}

#endif
