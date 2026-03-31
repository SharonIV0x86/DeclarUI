#pragma once
#include "../common/ast.h"
#include <fstream>
#include <string>

struct GenResult
{
    std::string id;
    bool isLayout;
};

class CodeGenerator
{
public:
    void generate(const Component *root);

private:
    std::ofstream out;
    int idCounter = 0;

    GenResult generateComponent(const Component *node);

    // 🔹 Component emitters
    GenResult emitWindow(const Component *node);
    GenResult emitButton(const Component *node);
    GenResult emitLabel(const Component *node);
    GenResult emitTextField(const Component *node);
    GenResult emitVBox(const Component *node);
    GenResult emitHBox(const Component *node);

    // 🔹 Property emitters
    void emitTitle(const std::string &id, const Component *node);
    void emitSize(const std::string &id, const Component *node);
    void emitText(const std::string &id, const Component *node);
    void emitPlaceholder(const std::string &id, const Component *node);
    void emitColor(const std::string &id, const Component *node);
};