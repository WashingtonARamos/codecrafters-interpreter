#include "../../inc/interpreter/context.h"
#include "../../inc/interpreter/fwd/lox_value.h"
#include "../../inc/interpreter/evaluation_interface.h"

#include <chrono>
#include <memory>
#include <unordered_map>

namespace lox::interpreter {

const std::unordered_map<std::string,
                         std::function<LoxValue(const std::vector<LoxValue> &)>>
    Environment::Builtins = {
        {"clock", [](const std::vector<LoxValue> & /*args*/) {
           const auto now = std::chrono::system_clock::now().time_since_epoch();
           return LoxValue{static_cast<double>(
               std::chrono::duration_cast<std::chrono::seconds>(now).count())};
         }}};

std::shared_ptr<LoxValue> Environment::Assign(const std::string &name,
                                              const LoxValue &value) {
  if (values_.contains(name)) {
    values_[name] = std::make_shared<LoxValue>(value);
    return nullptr;
  }
  return make_error("Undefined variable '" + name + "'.");
}

std::shared_ptr<LoxValue> Environment::AssignAt(const std::string &name,
                                                const LoxValue &value,
                                                const size_t distance) {
  auto *env = this;
  for (size_t i = 0; i < distance; ++i) {
    env = env->parent_.get();
  }
  return env->Assign(name, value);
}

std::shared_ptr<LoxValue> Environment::Declare(const std::string &name) {
  if (values_.contains(name)) {
    return make_error("Variable '" + name +
                      "' already declared in this scope.");
  }
  values_[name] = std::make_shared<LoxValue>();
  return nullptr;
}

std::shared_ptr<LoxValue> Environment::Get(const std::string &name) const {
  if (values_.contains(name)) {
    return values_.at(name);
  }
  return nullptr;
}

std::shared_ptr<LoxValue> Environment::GetAt(const std::string &name,
                                             const size_t distance) const {
  auto *env = this;
  for (size_t i = 0; i < distance; ++i) {
    env = env->parent_.get();
  }
  if (env == nullptr) {
    return GetFromParentRecursive(name);
  }
  return env->Get(name);
}

std::shared_ptr<LoxValue>
Environment::GetFromParentRecursive(const std::string &name) const {
  if (values_.contains(name)) {
    return values_.at(name);
  }

  if (parent_) {
    return parent_->GetFromParentRecursive(name);
  }

  return make_error("Undefined variable '" + name + "'.");
}

bool Environment::Contains(const std::string &name) const {
  return values_.contains(name);
}

} // namespace lox::interpreter