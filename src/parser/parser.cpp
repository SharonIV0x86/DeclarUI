#include "parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

Token Parser::lookahead() {
    return tokens[pos];
}

Token Parser::advance() {
    if (pos < tokens.size()) return tokens[pos++];
    return tokens.back();
}

bool Parser::match(TokenType type) {
    if (lookahead().type == type) {
        advance();
        return true;
    }
    return false;
}

void Parser::error(const std::string& msg) {
    std::cerr << "Parser Error: "<< msg << "\n";
    exit(1);
}

// P → C $
std::unique_ptr<Component> Parser::parseProgram() {
    auto root = parseC();

    if (!match(TokenType::END_OF_FILE)) {
        error("Expected end of file");
    }

    return root;
}

// C → T L B
std::unique_ptr<Component> Parser::parseC() {
    auto node = std::make_unique<Component>();

    node->type = parseT();          // T
    parseL(node->properties);       // L
    parseB(node->children);         // B

    return node;
}

// T → WINDOW | BUTTON | LABEL | TEXTFIELD | VBOX | HBOX
std::string Parser::parseT() {
    Token t = lookahead();

    switch (t.type) {
        case TokenType::WINDOW:   advance(); return "Window";
        case TokenType::BUTTON:   advance(); return "Button";
        case TokenType::LABEL:    advance(); return "Label";
        case TokenType::TEXTFIELD:advance(); return "TextField";
        case TokenType::VBOX:     advance(); return "VBox";
        case TokenType::HBOX:     advance(); return "HBox";
        default:
            error("Expected component type");
    }
    return "";
}

// L → R L | ε
void Parser::parseL(std::map<std::string,std::string>& props) {
    if (lookahead().type == TokenType::IDENTIFIER) {
        parseR(props);
        parseL(props);
    }
}

// R → IDENTIFIER = V
void Parser::parseR(std::map<std::string,std::string>& props) {
    Token key = lookahead();

    if (!match(TokenType::IDENTIFIER)) {
        error("Expected property name");
    }

    if (!match(TokenType::ASSIGN)) {
        error("Expected '='");
    }

    std::string value = parseV();

    props[key.lexeme] = value;
}

// V → STRING | NUMBER
std::string Parser::parseV() {
    Token t = lookahead();

    if (t.type == TokenType::STRING) {
        advance();
        return t.lexeme;
    }
    else if (t.type == TokenType::NUMBER) {
        advance();
        return t.lexeme;
    }

    error("Expected value");
    return "";
}

// B → { K } | ε
void Parser::parseB(std::vector<std::unique_ptr<Component>>& children) {
    if (match(TokenType::LBRACE)) {
        parseK(children);

        if (!match(TokenType::RBRACE)) {
            error("Expected '}'");
        }
    }
}

// K → C K | ε
void Parser::parseK(std::vector<std::unique_ptr<Component>>& children) {
    Token t = lookahead();

    if (t.type == TokenType::WINDOW ||
        t.type == TokenType::BUTTON ||
        t.type == TokenType::LABEL ||
        t.type == TokenType::TEXTFIELD ||
        t.type == TokenType::VBOX ||
        t.type == TokenType::HBOX) {

        children.push_back(parseC());
        parseK(children);
    }
}