#include <iostream>
#include "lexer/lexer_runner.h"
#include "semantic_analyzer/semantic_analyzer.h"
#include "parser/parser_runner.h"
#include "codegen/code_generator.h"
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: declarui <input_file>\n";
    return 1;
  }

  const char *inputFile = argv[1];
  const char *tokenFile = "phase-outputs/Phase_1_Lexical_tokens.txt";

  std::cout << "Phase 1: Lexical Analysis\n";
  runLexer(inputFile, tokenFile);

  std::cout << "Phase 2: Syntax Analysis\n";
  auto root = runParser(tokenFile);

  // Phase 3
  std::cout << "Phase 3: Semantic Analysis\n";
  SemanticAnalyzer semantic;
  semantic.analyze(root.get());

  // Phase 4
  std::cout << "Phase 4: Code Generation\n";
  CodeGenerator codegen;
  codegen.generate(root.get());
  std::cout << "Compilation finished.\n";

  return 0;
}