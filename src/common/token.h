#pragma once
#include <string>

enum class TokenType {
  WINDOW, BUTTON, LABEL, TEXTFIELD, VBOX, HBOX,
  IDENTIFIER, STRING, NUMBER,
  ASSIGN, LBRACE, RBRACE,
  END_OF_FILE, INVALID,
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;
};

inline TokenType tokenTypeFromString(const std::string& s) {
    if (s=="WINDOW") return TokenType::WINDOW;
    if (s=="BUTTON") return TokenType::BUTTON;
    if (s=="LABEL") return TokenType::LABEL;
    if (s=="TEXTFIELD") return TokenType::TEXTFIELD;
    if (s=="VBOX") return TokenType::VBOX;
    if (s=="HBOX") return TokenType::HBOX;
    if (s=="IDENTIFIER") return TokenType::IDENTIFIER;
    if (s=="STRING") return TokenType::STRING;
    if (s=="NUMBER") return TokenType::NUMBER;
    if (s=="ASSIGN") return TokenType::ASSIGN;
    if (s=="LBRACE") return TokenType::LBRACE;
    if (s=="RBRACE") return TokenType::RBRACE;
    if (s=="END_OF_FILE") return TokenType::END_OF_FILE;
    return TokenType::INVALID;
}