#include "lexer/lexer.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream file("UI-examples/login.d.ui");

  if (!file.is_open()) {
    std::cerr << "Error: Could not open input file\n";
    return 1;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  std::string source = buffer.str();

  Lexer lexer(source);
  lexer.debugPrint();

  return 0;
}
