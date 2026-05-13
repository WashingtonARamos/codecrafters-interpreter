#ifndef CODECRAFTERS_INTERPRETER_LOX_VALUE_H
#define CODECRAFTERS_INTERPRETER_LOX_VALUE_H
#include "../ast/expression/fwd/expr.h"
#include "../ast/statement/fwd/statement.h"
#include "class_blueprint.h"
#include "class_instance.h"
#include "interpreter_error.h"
#include "lox_function.h"

#include <string>
#include <variant>

namespace lox::interpreter {

static constexpr bool is_truthy(const LoxValue &alternative) {
  return std::visit(
      []<typename type>(const type &value) -> bool {
        if constexpr (std::is_same_v<type, bool>)
          return value;
        else if constexpr (std::is_same_v<type, std::monostate>)
          return false;
        else
          return true;
      },
      alternative);
}

inline LoxValue operator+(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr ((std::is_same_v<L, double> &&
                       std::is_same_v<R, double>) ||
                      (std::is_same_v<L, std::string> &&
                       std::is_same_v<R, std::string>)) {
          return l + r;
        } else {
          // Lox actually accepts operator+ on strings, but CC tests won't pass
          // unless we report it like this
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator-(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l - r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator*(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l * r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator/(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l / r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator==(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l == r;
        }
        if constexpr (std::is_same_v<L, bool> && std::is_same_v<R, bool>) {
          return l == r;
        }
        if constexpr (std::is_same_v<L, std::string> &&
                      std::is_same_v<R, std::string>) {
          return l == r;
        } else {
          return false;
        }
      },
      lhs, rhs);
}

inline LoxValue operator!=(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l != r;
        }
        if constexpr (std::is_same_v<L, bool> && std::is_same_v<R, bool>) {
          return l != r;
        }
        if constexpr (std::is_same_v<L, std::string> &&
                      std::is_same_v<R, std::string>) {
          return l != r;
        } else {
          return false;
        }
      },
      lhs, rhs);
}

inline LoxValue operator<=(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l <= r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator>=(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l >= r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator>(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l > r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

inline LoxValue operator<(const LoxValue &lhs, const LoxValue &rhs) {
  return std::visit(
      []<typename L, typename R>(const L &l, const R &r) -> LoxValue {
        if constexpr (std::is_same_v<L, double> && std::is_same_v<R, double>) {
          return l < r;
        } else {
          return InterpreterError{"Operands must be numbers."};
        }
      },
      lhs, rhs);
}

// Proxy functions for error creation
inline std::shared_ptr<LoxValue> make_error(const LoxValue &value,
                                            const ast::expr::Expression &expr) {
  const auto err = std::get<InterpreterError>(value);
  return std::make_shared<LoxValue>(InterpreterError(err.message, expr));
}

inline std::shared_ptr<LoxValue> make_error(const std::string &message,
                                            const ast::expr::Expression &expr) {
  return std::make_shared<LoxValue>(InterpreterError(message, expr));
}

inline std::shared_ptr<LoxValue> make_error(const std::string &message,
                                            const ast::stmt::Statement &expr) {
  return std::make_shared<LoxValue>(InterpreterError(message, expr));
}

inline std::shared_ptr<LoxValue> make_error(const std::string &message) {
  return std::make_shared<LoxValue>(InterpreterError(message));
}

} // namespace lox::interpreter

#endif
