#ifndef CODECRAFTERS_INTERPRETER_BINDING_POWER_H
#define CODECRAFTERS_INTERPRETER_BINDING_POWER_H
#include "../lexer/token.h"

namespace lox::parser {

struct binding_power {
  int32_t lbp;
  int32_t rbp;
};

static constexpr binding_power infix_binding_power(const lexer::TokenType type) {
  switch (type) {
  // right-binders
  case lexer::TokenType::OR:
    return {10, 20};
  case lexer::TokenType::AND:
    return {30, 40};
  case lexer::TokenType::EQUALS:
  case lexer::TokenType::UNEQUAL:
    return {50, 60};
  case lexer::TokenType::LESS_THAN:
  case lexer::TokenType::GREATER_THAN:
  case lexer::TokenType::LESS_OR_EQUAL_TO:
  case lexer::TokenType::GREATER_OR_EQUAL_TO:
    return {70, 80};
  case lexer::TokenType::PLUS:
  case lexer::TokenType::MINUS:
    return {90, 100};
  case lexer::TokenType::STAR:
  case lexer::TokenType::SLASH:
    return {110, 120};
  // left-binders
  case lexer::TokenType::ASSIGN:
    return {20, 10};
  case lexer::TokenType::DOT:
    return {130, 140};
  case lexer::TokenType::LEFT_PAREN:
    return {150, 0};
  default:
    return {-1, -1};
  }
}

static constexpr int32_t prefix_binding_power(const lexer::TokenType type) {
  switch (type) {
  case lexer::TokenType::BANG:
  case lexer::TokenType::MINUS:
    return 130;
  default:
    return -1;
  }
}

}

#endif
