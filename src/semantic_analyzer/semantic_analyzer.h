#pragma once
#include "../common/ast.h"
#include <string>
#include <set>
class SemanticAnalyzer
{
public:
    void analyze(const Component *root);

private:
    void validateComponent(const Component *node, bool isRoot);

    // Component validators
    void validateWindow(const Component *node, bool isRoot);
    void validateButton(const Component *node);
    void validateLabel(const Component *node);
    void validateTextField(const Component *node);
    void validateLayout(const Component *node);

    // Helpers
    void checkAllowedProperties(const Component *node,
                                const std::set<std::string> &allowed);

    void checkRequiredProperty(const Component *node,
                               const std::string &prop);

    void checkNumber(const Component *node,
                     const std::string &prop);

    void checkNoChildren(const Component *node);

    void error(const std::string &msg);
    void checkColor(const Component *node);
};