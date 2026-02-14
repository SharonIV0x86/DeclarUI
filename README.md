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
