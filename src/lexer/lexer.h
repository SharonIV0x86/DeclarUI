#pragma once
#include "token.h"
#include <string>
#include <vector>
class Lexer {
public:
  Lexer(const std::string &source);
  void debugPrint() const;
  std::vector<Token> tokenize();

private:
  std::string source;
  size_t current;
  int line;

  char peek() const;
  char advance();
  bool isAtEnd() const;

  void skipWhitespace();
  Token scanToken();

  Token scanToken();

  Token identifier();
  Token number();
  Token stringLiteral();
};
