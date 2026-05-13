#ifndef CODECRAFTERS_INTERPRETER_CLASS_INSTANCE_H
#define CODECRAFTERS_INTERPRETER_CLASS_INSTANCE_H
#include "fwd/lox_value.h"

#include <memory>
#include <unordered_map>

namespace lox::interpreter {
struct ClassInstance {
  ClassInstance(const std::shared_ptr<ClassBlueprint> &blueprint,
                std::shared_ptr<Context> ctx)
    : blueprint(blueprint), ctx(std::move(ctx)) {}

  std::shared_ptr<ClassBlueprint> blueprint;
  std::shared_ptr<Context> ctx;
};
}

#endif