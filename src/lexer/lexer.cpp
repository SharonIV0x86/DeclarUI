#include "lexer.h"
#include <iostream>

Lexer::Lexer(const std::string &src) : source(src), current(0), line(1) {}

void Lexer::debugPrint() const
{
    std::cout << "----- SOURCE START -----\n";
    std::cout << source;
    std::cout << "\n----- SOURCE END -----\n";
}
char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';
    return source[current];
}
char Lexer::advance() { return source[current++]; }
bool Lexer::isAtEnd() const { return current >= source.length(); }
void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r')
        {
            advance();
        }
        else if (c == '\n')
        {
            line++;
            advance;
        }
        else
        {
            break;
        }
    }
}
std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!isAtEnd())
    {
        skipWhitespace();
        if (isAtEnd())
            break;
        tokens.push_back(scanToken());
    }
    tokens.push_back({TokenType::END_OF_FILE, "", line});
    return tokens;
}
Token Lexer::scanToken()
{
    char c = advance();
    if (std::isalpha(c))
        return identifier();
    if (std::isdigit(c))
        return number();

    switch (c)
    {
    case '=':
        return {TokenType::ASSIGN, "=", line};
        break;
    case '{':
        return {TokenType::LBRACE, "{", line};
        break;
    case '}':
        return {TokenType::RBRACE, "}", line};
        break;
    case '"':
        return stringLiteral();
    default:
        return {TokenType::INVALID, std::string(1, c), line};
        break;
    }
}

Token Lexer::identifier()
{
    size_t start = current - 1;

    while (std::isalnum(peek()) || peek() == '_')
        advance();

    std::string text = source.substr(start, current - start);

    if (text == "Window")
        return {TokenType::WINDOW, text, line};
    if (text == "Button")
        return {TokenType::BUTTON, text, line};
    if (text == "Label")
        return {TokenType::LABEL, text, line};
    if (text == "TextField")
        return {TokenType::TEXTFIELD, text, line};
    if (text == "VBox")
        return {TokenType::VBOX, text, line};
    if (text == "HBox")
        return {TokenType::HBOX, text, line};

    return {TokenType::IDENTIFIER, text, line};
}

Token Lexer::number()
{
    size_t start = current - 1;

    while (std::isdigit(peek()))
        advance();

    return {
        TokenType::NUMBER,
        source.substr(start, current - start),
        line};
}
Token Lexer::stringLiteral()
{
    size_t start = current;

    while (!isAtEnd() && peek() != '"')
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (isAtEnd())
    {
        return {TokenType::INVALID, "Unterminated string", line};
    }

    advance();

    return {
        TokenType::STRING,
        source.substr(start, current - start - 1),
        line};
}
