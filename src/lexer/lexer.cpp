#include "../../inc/lexer/lexer.h"
#include <utility>

namespace lox::lexer {
Lexer::Lexer(std::string_view &string_view) : sv(string_view) {}

Token Lexer::MakeToken(const TokenType type, const std::string &value) const {
  return Token{type, value, line_, line_pos_};
}

Token Lexer::SingleChar(const TokenType type) {
  return MakeToken(type, std::string(1, Advance()));
}

char Lexer::Advance() {
  const char c = sv[pos_];
  if (c == '\n') {
    ++line_;
    line_pos_ = 1;
  } else {
    ++line_pos_;
  }
  ++pos_;
  return c;
}

char Lexer::Peek() const {
  if (pos_ >= sv.size())
    return '\0';

  return sv[pos_];
}

Token Lexer::NextToken() {
  while (pos_ < sv.size() && std::isspace(static_cast<unsigned char>(Peek()))) {
    Advance();
  }

  if (pos_ >= sv.size())
    return MakeToken(TokenType::END_OF_FILE, "");

  const char c = Peek();

  if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
    std::string id;
    while (pos_ < sv.size() &&
           (std::isalpha(static_cast<unsigned char>(sv[pos_])) ||
            sv[pos_] == '_' ||
            std::isdigit(static_cast<unsigned char>(sv[pos_])))) {
      id += sv[pos_++];
    }

    if (id == "and")
      return MakeToken(TokenType::AND, "AND");
    if (id == "class")
      return MakeToken(TokenType::CLASS, "CLASS");
    if (id == "else")
      return MakeToken(TokenType::ELSE, "ELSE");
    if (id == "false")
      return MakeToken(TokenType::FALSE, "FALSE");
    if (id == "fun")
      return MakeToken(TokenType::FUN, "FUN");
    if (id == "for")
      return MakeToken(TokenType::FOR, "FOR");
    if (id == "if")
      return MakeToken(TokenType::IF, "IF");
    if (id == "nil")
      return MakeToken(TokenType::NIL, "NIL");
    if (id == "or")
      return MakeToken(TokenType::OR, "OR");
    if (id == "print")
      return MakeToken(TokenType::PRINT, "PRINT");
    if (id == "return")
      return MakeToken(TokenType::RETURN, "RETURN");
    if (id == "super")
      return MakeToken(TokenType::SUPER, "super");
    if (id == "this")
      return MakeToken(TokenType::THIS, "this");
    if (id == "true")
      return MakeToken(TokenType::TRUE, "TRUE");
    if (id == "var")
      return MakeToken(TokenType::VAR, "VAR");
    if (id == "while")
      return MakeToken(TokenType::WHILE, "WHILE");

    return MakeToken(TokenType::IDENTIFIER, id);
  }

  if (c == '\"') {
    Advance();
    std::string str;

    while (pos_ < sv.size() && Peek() != '\"') {
      str += Advance();
    }

    if (pos_ >= sv.size()) {
      return MakeToken(TokenType::UNTERMINATED_STRING, "\"");
    }

    Advance();
    return MakeToken(TokenType::STRING, str);
  }

  if (std::isdigit(static_cast<unsigned char>(c))) {
    std::string num_str;
    while (pos_ < sv.size() &&
           (std::isdigit(static_cast<unsigned char>(sv[pos_])) ||
            sv[pos_] == '.')) {
      num_str += Advance();
    }
    return MakeToken(TokenType::NUMBER, num_str);
  }

  switch (c) {
  case '(':
    return SingleChar(TokenType::LEFT_PAREN);
  case ')':
    return SingleChar(TokenType::RIGHT_PAREN);
  case '{':
    return SingleChar(TokenType::LEFT_BRACE);
  case '}':
    return SingleChar(TokenType::RIGHT_BRACE);
  case '[':
    return SingleChar(TokenType::LEFT_BRACKET);
  case ']':
    return SingleChar(TokenType::RIGHT_BRACKET);
  case '.':
    return SingleChar(TokenType::DOT);
  case ',':
    return SingleChar(TokenType::COMMA);
  case '-':
    return SingleChar(TokenType::MINUS);
  case '+':
    return SingleChar(TokenType::PLUS);
  case '*':
    return SingleChar(TokenType::STAR);
  case ';':
    return SingleChar(TokenType::SEMICOLON);
  case '/':
    if (pos_ + 1 < sv.size() && sv[pos_ + 1] == '/') {
      while (pos_ < sv.size() && sv[pos_] != '\n')
        ++pos_;
      if (pos_ < sv.size())
        ++pos_;
      ++line_;
      return NextToken();
    }
    return SingleChar(TokenType::SLASH);
  case '=':
    if (pos_ + 1 < sv.size() && sv[pos_ + 1] == '=') {
      pos_ += 2;
      return MakeToken(TokenType::EQUALS, "==");
    }
    return SingleChar(TokenType::ASSIGN);
  case '!':
    if (pos_ + 1 < sv.size() && sv[pos_ + 1] == '=') {
      pos_ += 2;
      return MakeToken(TokenType::UNEQUAL, "!=");
    }
    return SingleChar(TokenType::BANG);
  case '<':
    if (pos_ + 1 < sv.size() && sv[pos_ + 1] == '=') {
      pos_ += 2;
      return MakeToken(TokenType::LESS_OR_EQUAL_TO, "<=");
    }
    return SingleChar(TokenType::LESS_THAN);
  case '>':
    if (pos_ + 1 < sv.size() && sv[pos_ + 1] == '=') {
      pos_ += 2;
      return MakeToken(TokenType::GREATER_OR_EQUAL_TO, ">=");
    }
    return SingleChar(TokenType::GREATER_THAN);
  default:
    Advance();
    return Token{TokenType::UNEXPECTED_TOKEN, std::string{c}, line_};
  }
}

Token Lexer::PeekNext() const {
  Lexer temp = *this;
  return temp.NextToken();
}

} // namespace lox::lexer
