#include "code_generator.h"
#include <iostream>

// MAIN
void CodeGenerator::generate(const Component *root)
{

    out.open("phase-outputs/output.cpp");

    out << "#include <QApplication>\n";
    out << "#include <QWidget>\n";
    out << "#include <QPushButton>\n";
    out << "#include <QLabel>\n";
    out << "#include <QLineEdit>\n";
    out << "#include <QVBoxLayout>\n";
    out << "#include <QHBoxLayout>\n\n";

    out << "int main(int argc, char *argv[]) {\n";
    out << "    QApplication app(argc, argv);\n\n";

    generateComponent(root);

    out << "    return app.exec();\n";
    out << "}\n";

    out.close();

    std::cout << "Code Generation completed.\n";
}

// DISPATCH

GenResult CodeGenerator::generateComponent(const Component *node)
{

    if (node->type == "Window")
        return emitWindow(node);
    if (node->type == "Button")
        return emitButton(node);
    if (node->type == "Label")
        return emitLabel(node);
    if (node->type == "TextField")
        return emitTextField(node);
    if (node->type == "VBox")
        return emitVBox(node);
    if (node->type == "HBox")
        return emitHBox(node);

    std::cerr << "Unknown component: " << node->type << "\n";
    exit(1);
}

// COMPONENT EMITTERS

GenResult CodeGenerator::emitWindow(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QWidget *" << id << " = new QWidget();\n";

    emitTitle(id, node);
    emitSize(id, node);
    emitColor(id, node);
    std::string layoutId = "layout" + id;
    out << "    QVBoxLayout *" << layoutId << " = new QVBoxLayout();\n";

    for (auto &child : node->children)
    {
        GenResult c = generateComponent(child.get());

        if (c.isLayout)
            out << "    " << layoutId << "->addLayout(" << c.id << ");\n";
        else
            out << "    " << layoutId << "->addWidget(" << c.id << ");\n";
    }

    out << "    " << id << "->setLayout(" << layoutId << ");\n";
    out << "    " << id << "->show();\n";
    out << "    " << id << "->setAutoFillBackground(true);\n";
    return {id, false}; // QWidget
}

GenResult CodeGenerator::emitButton(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QPushButton *" << id << " = new QPushButton();\n";

    emitText(id, node);
    emitColor(id, node);
    return {id, false};
}

GenResult CodeGenerator::emitLabel(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QLabel *" << id << " = new QLabel();\n";

    emitText(id, node);
    emitColor(id, node);
    return {id, false};
}

GenResult CodeGenerator::emitTextField(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QLineEdit *" << id << " = new QLineEdit();\n";

    emitPlaceholder(id, node);

    return {id, false};
}

GenResult CodeGenerator::emitVBox(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QVBoxLayout *" << id << " = new QVBoxLayout();\n";

    for (auto &child : node->children)
    {
        GenResult c = generateComponent(child.get());

        if (c.isLayout)
            out << "    " << id << "->addLayout(" << c.id << ");\n";
        else
            out << "    " << id << "->addWidget(" << c.id << ");\n";
    }

    return {id, true}; // Layout
}

GenResult CodeGenerator::emitHBox(const Component *node)
{

    std::string id = "comp" + std::to_string(idCounter++);

    out << "    QHBoxLayout *" << id << " = new QHBoxLayout();\n";

    for (auto &child : node->children)
    {
        GenResult c = generateComponent(child.get());

        if (c.isLayout)
            out << "    " << id << "->addLayout(" << c.id << ");\n";
        else
            out << "    " << id << "->addWidget(" << c.id << ");\n";
    }

    return {id, true};
}

// PROPERTY EMITTERS

void CodeGenerator::emitTitle(const std::string &id, const Component *node)
{

    if (node->properties.count("title"))
    {
        out << "    " << id << "->setWindowTitle(\""
            << node->properties.at("title") << "\");\n";
    }
}

void CodeGenerator::emitSize(const std::string &id, const Component *node)
{

    std::string width = node->properties.count("width") ? node->properties.at("width") : "800";
    std::string height = node->properties.count("height") ? node->properties.at("height") : "600";

    out << "    " << id << "->resize(" << width << ", " << height << ");\n";
}

void CodeGenerator::emitText(const std::string &id, const Component *node)
{
    emitColor(id, node);
    if (node->properties.count("text"))
    {
        out << "    " << id << "->setText(\""
            << node->properties.at("text") << "\");\n";
    }
}

void CodeGenerator::emitPlaceholder(const std::string &id, const Component *node)
{

    if (node->properties.count("placeholder"))
    {
        out << "    " << id << "->setPlaceholderText(\""
            << node->properties.at("placeholder") << "\");\n";
    }
}
void CodeGenerator::emitColor(const std::string &id, const Component *node)
{

    if (!node->properties.count("color"))
        return;

    std::string val = node->properties.at("color");

    if (node->type == "Window")
    {
        out << "    " << id << "->setStyleSheet(\"background-color: "
            << val << ";\");\n";
    }
    else
    {
        out << "    " << id << "->setStyleSheet(\"color: "
            << val << ";\");\n";
    }
}