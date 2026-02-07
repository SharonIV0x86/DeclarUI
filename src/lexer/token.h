#pragma once
#include <string>
enum class TokenType {
  WINDOW,
  BUTTON,
  LABEL,
  TEXTFIELD,
  VBOX,
  HBOX,

  IDENTIFIER,
  STRING,
  NUMBER,

  ASSIGN,
  LBRACE,
  RBRACE,

  END_OF_FILE,
  INVALID,
};
struct Token {
  TokenType type;
  std::string lexeme;
  int line;
};
