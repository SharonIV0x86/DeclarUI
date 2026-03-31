// NOTE: THIS FILE IS NOT FOR THE SAKE OF INDEPENDENT COMPILATION OF THE PARSER, IT IS NOT BEING USED IN THE PARSER CODE.

// #include "../common/token.h"
// #include "../common/ast.h"
// #include "parser.h"
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <string>

// static inline std::string trim(const std::string& s) {
//     if (s.empty()) return s;
//     size_t i=0, j=s.size();
//     while (i<j && isspace((unsigned char)s[i])) ++i;
//     while (j>i && isspace((unsigned char)s[j-1])) --j;
//     return s.substr(i, j-i);
// }

// std::vector<Token> readTokenFile(const std::string& path) {
//     std::vector<Token> tokens;
//     std::ifstream in(path);
//     if (!in) throw std::runtime_error("Cannot open tokens file");
//     std::string line;
//     while (std::getline(in, line)) {
//         if (line.empty()) continue;
//         std::string typeStr, lexeme, lineStr;
//         std::istringstream ss(line);
//         std::getline(ss, typeStr, '\t');
//         std::getline(ss, lexeme, '\t');
//         std::getline(ss, lineStr, '\t');
//         Token t;
//         t.type = tokenTypeFromString(trim(typeStr));
//         t.lexeme = trim(lexeme);
//         t.line = std::stoi(trim(lineStr));
//         tokens.push_back(t);
//         if (t.type == TokenType::END_OF_FILE) break;
//     }
//     if (tokens.empty() || tokens.back().type != TokenType::END_OF_FILE) {
//         Token e; e.type = TokenType::END_OF_FILE; e.lexeme = "-"; e.line = 0;
//         tokens.push_back(e);
//     }
//     return tokens;
// }

// void printAST(const Component* node, int depth=0) {
//     std::string indent(depth*2,' ');
//     std::cout << indent << node->type;
//     if (!node->properties.empty()) {
//         std::cout << " { ";
//         for (auto &p : node->properties) {
//             std::cout << p.first << "=\"" << p.second << "\" ";
//         }
//         std::cout << " }";
//     }
//     std::cout << "\n";
//     for (const auto &c : node->children) printAST(c.get(), depth+1);
// }

// int main(int argc, char** argv) {
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " <tokens.txt>\n";
//         return 1;
//     }
//     try {
//         auto tokens = readTokenFile(argv[1]);
//         Parser parser(tokens);
//         auto root = parser.parseProgram();
//         std::cout << "=== AST ===\n";
//         printAST(root.get());
//     } catch (std::exception &ex) {
//         std::cerr << "Error: " << ex.what() << "\n";
//         return 1;
//     }
//     return 0;
// }