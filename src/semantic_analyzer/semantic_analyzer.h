#pragma once
#include "../common/ast.h"

class SemanticAnalyzer
{
public:
    void analyze(Component *root);

private:
    void checkComponent(Component *node);
};