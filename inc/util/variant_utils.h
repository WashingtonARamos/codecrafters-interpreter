#ifndef CODECRAFTERS_INTERPRETER_VARIANT_UTILS_H
#define CODECRAFTERS_INTERPRETER_VARIANT_UTILS_H
#include <variant>
#include <type_traits>

template <typename T, typename Variant>
struct is_alternative;

template <typename T, typename... Types>
struct is_alternative<T, std::variant<Types...>>
    : std::bool_constant<(std::is_same_v<T, Types> || ...)> {};

#endif
