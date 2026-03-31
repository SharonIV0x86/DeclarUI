# DeclarUI
A Declarative UI Language Compiler for Generating C++ GUIs

# Compiling
1. Generate the lexer.
```
flex --c++ src/lexer/lexer.l 
```

2. Compile using the lexer.

```
g++ src/main.cpp src/lexer/lex.yy.cc -o declarui
```

# 1 Language Constructs
## 1.1 Components
| Component   | Description                 |
| ----------- | --------------------------- |
| `Window`    | Top-level container         |
| `Button`    | Clickable button            |
| `Label`     | Static text                 |
| `TextField` | Text input                  |
| `VBox`      | Vertical layout container   |
| `HBox`      | Horizontal layout container |

## 1.2 Properties

**property syntax:** 
```
PropertyName = value
```

**Example:**
```
Button text="Submit" width=120
```

## 1.3 Hierarchy

For hierarchy example see: [hierarchy-eample.d.ui](UI-examples/hierarchy-example.d.ui)

| Parent          | Allowed Children                               |
| --------------- | ---------------------------------------------- |
| `Window`        | `VBox`, `HBox`, `Button`, `Label`, `TextField` |
| `VBox` / `HBox` | `Button`, `Label`, `TextField`, `VBox`, `HBox` |
| `Button`        | ❌ none                                         |
| `Label`         | ❌ none                                         |
| `TextField`     | ❌ none                                         |

# 2 Compiling and Building
From the root level of the project, follow below steps.
### Step 1 Run the Lexical Analyzer
> gcc -c src/lexer/lexer.c -o lexer.o
### Step 2 Compile All the files
> g++ -std=c++17 \
src/main.cpp \
lexer.o \
src/lexer/lexer_runner.cpp \
src/parser/parser.cpp \
src/parser/parser_runner.cpp \
src/semantic_analyzer/semantic_analyzer.cpp \
src/codegen/code_generator.cpp \
-lfl \
-o declarui

After step 2, you can run the executable file that will be created in the root level of the project named as ``declarui``.

# Parser Grammar
For our compiler we are using a LL(1) parser for which the grammar is defined below
## Non Terminals
| Symbol | Meaning       | Real-world       |
| ------ | ------------- | ---------------- |
| P      | Program       | Entire UI        |
| C      | Component     | UI element       |
| T      | Type          | Button / Window  |
| L      | PropertyList  | All properties   |
| R      | Property      | One property     |
| V      | Value         | Property value   |
| B      | Block         | Children section |
| K      | ComponentList | List of children |
## Terminal Symbols
```
w → WINDOW
b → BUTTON
l → LABEL
t → TEXTFIELD
v → VBOX
h → HBOX
i → IDENTIFIER
s → STRING
n → NUMBER
= → ASSIGN
{ → LBRACE
} → RBRACE
$ → EOF
```
## Parser Grammar
```
P → C $

C → T L B

T → w | b | l | t | v | h

L → R L | ε

R → i = V

V → s | n

B → { K } | ε

K → C K | ε
```
## LL(1) Parsing Table
| NT \ T | w | b | l | t | v | h | i | s | n | { | } | $ |
|--------|---|---|---|---|---|---|---|---|---|---|---|---|
| P      | P→C$ | P→C$ | P→C$ | P→C$ | P→C$ | P→C$ |   |   |   |   |   |   |
| C      | C→TLB | C→TLB | C→TLB | C→TLB | C→TLB | C→TLB |   |   |   |   |   |   |
| T      | T→w | T→b | T→l | T→t | T→v | T→h |   |   |   |   |   |   |
| L      |   |   |   |   |   |   | L→RL |   |   | L→ε | L→ε | L→ε |
| R      |   |   |   |   |   |   | R→i=V |   |   |   |   |   |
| V      |   |   |   |   |   |   |   | V→s | V→n |   |   |   |
| B      |   |   |   |   |   |   |   |   |   | B→{K} | B→ε | B→ε |
| K      | K→CK | K→CK | K→CK | K→CK | K→CK | K→CK |   |   |   |   | K→ε |   |