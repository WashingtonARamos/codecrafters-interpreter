#include "../../inc/lexer/token.h"
#include <format>
#include <utility>

namespace lox::lexer {
  std::string to_string(const Token& token) {
    switch (token.type) {
      case TokenType::LEFT_PAREN:             return "LEFT_PAREN ( null";
      case TokenType::RIGHT_PAREN:            return "RIGHT_PAREN ) null";
      case TokenType::LEFT_BRACE:             return "LEFT_BRACE { null";
      case TokenType::RIGHT_BRACE:            return "RIGHT_BRACE } null";
      case TokenType::LEFT_BRACKET:           return "LEFT_BRACKET [ null";
      case TokenType::RIGHT_BRACKET:          return "RIGHT_BRACKET ] null";
      case TokenType::IDENTIFIER:             return "IDENTIFIER " + token.value + " null";
      case TokenType::COMMA:                  return "COMMA , null";
      case TokenType::DOT:                    return "DOT . null";
      case TokenType::MINUS:                  return "MINUS - null";
      case TokenType::PLUS:                   return "PLUS + null";
      case TokenType::SEMICOLON:              return "SEMICOLON ; null";
      case TokenType::SLASH:                  return "SLASH / null";
      case TokenType::STAR:                   return "STAR * null";
      case TokenType::ASSIGN:                 return "EQUAL = null";
      case TokenType::EQUALS:                 return "EQUAL_EQUAL == null";
      case TokenType::BANG:                   return "BANG ! null";
      case TokenType::UNEQUAL:                return "BANG_EQUAL != null";
      case TokenType::LESS_THAN:              return "LESS < null";
      case TokenType::GREATER_THAN:           return "GREATER > null";
      case TokenType::LESS_OR_EQUAL_TO:       return "LESS_EQUAL <= null";
      case TokenType::GREATER_OR_EQUAL_TO:    return "GREATER_EQUAL >= null";
      case TokenType::STRING:                 return "STRING \"" + token.value + "\" " + token.value;
      case TokenType::AND:                    return "AND and null";
      case TokenType::CLASS:                  return "CLASS class null";
      case TokenType::ELSE:                   return "ELSE else null";
      case TokenType::FALSE:                  return "FALSE false null";
      case TokenType::FUN:                    return "FUN fun null";
      case TokenType::FOR:                    return "FOR for null";
      case TokenType::IF:                     return "IF if null";
      case TokenType::NIL:                    return "NIL nil null";
      case TokenType::OR:                     return "OR or null";
      case TokenType::PRINT:                  return "PRINT print null";
      case TokenType::RETURN:                 return "RETURN return null";
      case TokenType::SUPER:                  return "SUPER super null";
      case TokenType::THIS:                   return "THIS this null";
      case TokenType::TRUE:                   return "TRUE true null";
      case TokenType::VAR:                    return "VAR var null";
      case TokenType::WHILE:                  return "WHILE while null";
      case TokenType::NEW_LINE:               return "NEW_LINE new_line null";
      case TokenType::END_OF_FILE:            return "EOF  null";
      case TokenType::UNTERMINATED_STRING:
        return "[line " + std::to_string(token.line) + "] Error: Unterminated string.";
      case TokenType::UNEXPECTED_TOKEN:
        return "[line " + std::to_string(token.line) + "] Error: Unexpected character: " + token.value;
      case TokenType::NUMBER: {
        std::string formatted = std::format("{}", std::stod(token.value));
        if (formatted.find('.') == std::string::npos)
          formatted += ".0";
        return "NUMBER " + token.value + " " + formatted;
      }
    }
    std::unreachable();
  }
}
