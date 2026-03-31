#include "semantic_analyzer.h"
#include <iostream>
#include <set>
#include <cctype>

//////////////////////////////////////////////////////
// CORE
//////////////////////////////////////////////////////

void SemanticAnalyzer::error(const std::string &msg)
{
    std::cerr << "Semantic Error: " << msg << "\n";
    exit(1);
}

void SemanticAnalyzer::analyze(const Component *root)
{
    validateComponent(root, true);
    std::cout << "Semantic Analysis completed successfully.\n";
}

//////////////////////////////////////////////////////
// DISPATCH
//////////////////////////////////////////////////////

void SemanticAnalyzer::validateComponent(const Component *node, bool isRoot)
{
    if (node->type == "Window")
        validateWindow(node, isRoot);
    else if (node->type == "Button")
        validateButton(node);
    else if (node->type == "Label")
        validateLabel(node);
    else if (node->type == "TextField")
        validateTextField(node);
    else if (node->type == "VBox" || node->type == "HBox")
        validateLayout(node);
    else
        error("Unknown component: " + node->type);

    // 🔹 Recurse
    for (auto &child : node->children)
    {
        validateComponent(child.get(), false);
    }
}

//////////////////////////////////////////////////////
// COMPONENT VALIDATORS
//////////////////////////////////////////////////////

void SemanticAnalyzer::validateWindow(const Component *node, bool isRoot)
{
    if (!isRoot)
    {
        error("Window can only be root");
    }

    checkAllowedProperties(node, {"title", "width", "height", "color"});
    checkRequiredProperty(node, "title");
    checkColor(node);
    checkNumber(node, "width");
    checkNumber(node, "height");
}

void SemanticAnalyzer::validateButton(const Component *node)
{
    checkAllowedProperties(node, {"text", "color"});
    checkRequiredProperty(node, "text");
    checkColor(node);
    checkNoChildren(node);
}

void SemanticAnalyzer::validateLabel(const Component *node)
{
    checkAllowedProperties(node, {"text", "color"});
    checkRequiredProperty(node, "text");
    checkColor(node);
    checkNoChildren(node);
}

void SemanticAnalyzer::validateTextField(const Component *node)
{
    checkAllowedProperties(node, {"placeholder"});
    checkNoChildren(node);
}

void SemanticAnalyzer::validateLayout(const Component *node)
{
    checkAllowedProperties(node, {});
    // layouts can have children → no restriction here
}

//////////////////////////////////////////////////////
// HELPERS
//////////////////////////////////////////////////////

void SemanticAnalyzer::checkAllowedProperties(
    const Component *node,
    const std::set<std::string> &allowed)
{
    for (auto &p : node->properties)
    {
        if (!allowed.count(p.first))
        {
            error("Invalid property '" + p.first + "' for " + node->type);
        }
    }
}

void SemanticAnalyzer::checkRequiredProperty(
    const Component *node,
    const std::string &prop)
{
    if (!node->properties.count(prop))
    {
        error(node->type + " must have '" + prop + "'");
    }
}

void SemanticAnalyzer::checkNumber(
    const Component *node,
    const std::string &prop)
{
    if (!node->properties.count(prop))
        return;

    const std::string &val = node->properties.at(prop);

    for (char c : val)
    {
        if (!isdigit(c))
        {
            error(prop + " must be a number in " + node->type);
        }
    }
}

void SemanticAnalyzer::checkNoChildren(const Component *node)
{
    if (!node->children.empty())
    {
        error(node->type + " cannot have children");
    }
}
void SemanticAnalyzer::checkColor(const Component *node)
{

    if (!node->properties.count("color"))
        return;

    std::string val = node->properties.at("color");

    // very basic validation (you can expand later)
    if (val.empty())
    {
        error("color cannot be empty");
    }
}