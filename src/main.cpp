#include <iostream>
#include "lexer/lexer_runner.h"
#include "parser/parser_runner.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: declarui <input_file>\n";
    return 1;
  }

  const char *inputFile = argv[1];
  const char *tokenFile = "phase-outputs/Phase_1_Lexical_tokens.txt";

  std::cout << "===== DeclarUI Compiler =====\n";

  std::cout << "Phase 1: Lexical Analysis\n";
  runLexer(inputFile, tokenFile);

  std::cout << "Phase 2: Syntax Analysis\n";
  runParser(tokenFile);

  std::cout << "Compilation finished.\n";

  return 0;
}