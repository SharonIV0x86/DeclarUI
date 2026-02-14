#include <iostream>
#include <fstream>
#include <FlexLexer.h>

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: ./declarui <file>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  yyFlexLexer lexer(&file);

  while (lexer.yylex() != 0)
  {
    // tokens are printed inside lexer rules
  }

  return 0;
}
int yyFlexLexer::yywrap() { return 1; }