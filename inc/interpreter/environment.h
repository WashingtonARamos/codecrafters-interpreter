#ifndef CODECRAFTERS_INTERPRETER_ENVIRONMENT_H
#define CODECRAFTERS_INTERPRETER_ENVIRONMENT_H
#include "fwd/lox_value.h"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace lox::interpreter {
struct Context;

struct Environment {
  Environment() : parent_(nullptr) {}
  explicit Environment(std::shared_ptr<Environment> parent)
      : parent_(std::move(parent)) {}
  Environment &operator=(const Environment &) = delete;

  static const std::unordered_map<
      std::string, std::function<LoxValue(const std::vector<LoxValue> &)>>
      Builtins;

  [[nodiscard]] std::shared_ptr<LoxValue>
  Assign(const std::string &name, const LoxValue &value);
  [[nodiscard]] std::shared_ptr<LoxValue>
  AssignAt(const std::string &name, const LoxValue &value, size_t distance);

  [[nodiscard]] std::shared_ptr<LoxValue>
  Declare(const std::string &name);

  [[nodiscard]] std::shared_ptr<LoxValue>
  Get(const std::string &name) const;
  [[nodiscard]] std::shared_ptr<LoxValue>
  GetAt(const std::string &name, size_t distance) const;
  std::shared_ptr<LoxValue>
  GetFromParentRecursive(const std::string &name) const;

  bool Contains(const std::string &name) const;

private:
  std::unordered_map<std::string, std::shared_ptr<LoxValue>> values_;
  std::shared_ptr<Environment> parent_;
};

} // namespace lox::interpreter

#endif