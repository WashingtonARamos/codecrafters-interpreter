#include "../inc/ast/statement/statement.h"
#include "../inc/interpreter/evaluation_interface.h"
#include "../inc/lexer/lexer.h"
#include "../inc/parser/parser.h"
#include "../inc/util/ast_printer.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::string read_file_contents(const std::string &filename);

int main(int argc, char *argv[]) {
  // Disable output buffering
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cerr << "Logs from your program will appear here!" << std::endl;

  if (argc < 3) {
    std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
    return 1;
  }

  const std::string command = argv[1];

  if (command == "tokenize") {
    const auto file_contents = read_file_contents(argv[2]);
    std::string_view sv = file_contents;
    lox::lexer::Lexer lexer(sv);
    auto cur_token = lexer.NextToken();
    bool errors = false;
    while (!is_eof(cur_token)) {
      if (is_bad_token(cur_token)) {
        std::cerr << to_string(cur_token) << std::endl;
        cur_token = lexer.NextToken();
        errors = true;
        continue;
      }
      // Challenge doesn't require you to print new lines
      if (cur_token.type != lox::lexer::TokenType::NEW_LINE)
        std::cout << to_string(cur_token) << std::endl;
      cur_token = lexer.NextToken();
    }

    std::cout << to_string(cur_token) << std::endl;
    return errors ? 65 : 0;
  } else if (command == "parse") {
    const auto file_contents_str = read_file_contents(argv[2]);
    std::string_view sv = file_contents_str;
    lox::lexer::Lexer lexer(sv);
    lox::parser::Parser parser(lexer);

    auto tree = parser.ParseExpression(0);

    if (!parser.errors().empty()) {
      for (const auto &error : parser.errors())
        std::cerr << error.message << std::endl;
      return 65;
    }
    std::cout << lox::util::PrintAst(tree) << std::endl;
    return 0;
  } else if (command == "evaluate") {
    const auto file_contents = read_file_contents(argv[2]);
    std::string_view sv = file_contents;
    lox::lexer::Lexer lexer(sv);
    lox::parser::Parser parser(lexer);
    auto tree = parser.ParseExpression(0);

    if (!parser.errors().empty()) {
      for (const auto &error : parser.errors())
        std::cerr << error.message << std::endl;
      return 65;
    }

    auto output = lox::interpreter::Evaluate(tree);
    if (std::holds_alternative<lox::interpreter::InterpreterError>(output)) {
      std::cerr << lox::interpreter::ToString(output) << std::endl;
      return 70;
    }
    std::cout << lox::interpreter::ToString(output) << std::endl;
    return 0;
  } else if (command == "run") {
    const auto file_contents = read_file_contents(argv[2]);
    std::string_view sv = file_contents;
    lox::lexer::Lexer lexer(sv);
    lox::parser::Parser parser(lexer);
    auto program = parser.ParseProgram();
    if (!parser.errors().empty()) {
      for (const auto &error : parser.errors())
        std::cerr << error.message << std::endl;
      return 65;
    }

    auto exec_res = lox::interpreter::Execute(program);
    if (!exec_res)
      return 0;

    if (std::holds_alternative<lox::interpreter::InterpreterError>(*exec_res)) {
      auto err = std::get<lox::interpreter::InterpreterError>(*exec_res);
      if (err.message == "Errors detected during pre-analysis")
        return 65;
      std::cerr << ToString(*exec_res) << std::endl;
      return 70;
    }
    return 0;
  }
}

static std::string read_file_contents(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error reading file: " << filename << std::endl;
    std::exit(1);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  return buffer.str();
}
