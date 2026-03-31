#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

struct Component {
    std::string type; // "Window", "Button", ...
    std::map<std::string,std::string> properties;
    std::vector<std::unique_ptr<Component>> children;
};