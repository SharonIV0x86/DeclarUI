#pragma once
#include <memory>
#include "../common/ast.h"
std::unique_ptr<Component> runParser(const char *tokenFile);