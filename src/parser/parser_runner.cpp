#include "parser_runner.h"
#include "../common/token.h"
#include "../common/ast.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

static std::string trim(const std::string &s)
{
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i]))
        ++i;
    while (j > i && isspace((unsigned char)s[j - 1]))
        --j;
    return s.substr(i, j - i);
}

std::vector<Token> readTokenFile(const std::string &path)
{
    std::vector<Token> tokens;
    std::ifstream in(path);

    std::string line;
    while (getline(in, line))
    {
        std::stringstream ss(line);

        std::string typeStr, lexeme, lineStr;

        getline(ss, typeStr, '\t');
        getline(ss, lexeme, '\t');
        getline(ss, lineStr, '\t');

        Token t;
        t.type = tokenTypeFromString(trim(typeStr));
        t.lexeme = trim(lexeme);
        t.line = stoi(trim(lineStr));

        tokens.push_back(t);
    }

    tokens.push_back({TokenType::END_OF_FILE, "-", 0});
    return tokens;
}

void printAST(const Component *node, std::ostream &out, int depth = 0)
{
    std::string indent(depth * 2, ' ');

    out << indent << node->type;

    if (!node->properties.empty())
    {
        out << " { ";
        for (auto &p : node->properties)
        {
            out << p.first << "=" << p.second << " ";
        }
        out << "}";
    }

    out << "\n";

    for (auto &c : node->children)
    {
        printAST(c.get(), out, depth + 1);
    }
}

void runParser(const char *tokenFile)
{
    try
    {
        auto tokens = readTokenFile(tokenFile);

        Parser parser(tokens);
        auto root = parser.parseProgram();

        std::ofstream out("phase-outputs/Phase_2_Parsing_ast.txt");
        out << "=== AST ===\n";
        printAST(root.get(), out);

        std::cout << "Parser completed. AST written to ast.txt\n";
    }
    catch (std::exception &e)
    {
        std::cerr << "Parser Error: " << e.what() << "\n";
    }
}