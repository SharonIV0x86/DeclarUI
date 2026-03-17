#pragma once
#include "../common/token.h"
#include "../common/ast.h"
#include <vector>
#include <memory>

class Parser
{
private:
    std::vector<Token> tokens;
    int pos = 0;

    Token lookahead();
    Token advance();
    bool match(TokenType type);

    void error(const std::string &msg);

    // Grammar functions
    std::unique_ptr<Component> parseC();
    std::string parseT();
    void parseL(std::map<std::string, std::string> &props);
    void parseR(std::map<std::string, std::string> &props);
    std::string parseV();
    void parseB(std::vector<std::unique_ptr<Component>> &children);
    void parseK(std::vector<std::unique_ptr<Component>> &children);

public:
    Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Component> parseProgram();
};