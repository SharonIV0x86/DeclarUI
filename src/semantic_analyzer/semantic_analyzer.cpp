#include "semantic_analyzer.h"
#include <iostream>

void SemanticAnalyzer::analyze(Component* root) {
    checkComponent(root);
}

void SemanticAnalyzer::checkComponent(Component* node) {

    if (node->type == "Window") {
        if (node->properties.find("title") == node->properties.end()) {
            std::cerr << "Semantic Error: Window must have a title\n";
        }
    }

    if (node->type == "Button") {
        if (!node->children.empty()) {
            std::cerr << "Semantic Error: Button cannot contain children\n";
        }
    }

    for (auto &child : node->children) {
        checkComponent(child.get());
    }
}