%{
#include <iostream>
#include "token.h"

int line = 1;
%}

%%

"Window"      { std::cout << "WINDOW\n"; }
"Button"      { std::cout << "BUTTON\n"; }
"Label"       { std::cout << "LABEL\n"; }
"TextField"   { std::cout << "TEXTFIELD\n"; }
"VBox"        { std::cout << "VBOX\n"; }
"HBox"        { std::cout << "HBOX\n"; }

[0-9]+        { std::cout << "NUMBER: " << yytext << "\n"; }

\"([^"]*)\"   { std::cout << "STRING: " << yytext << "\n"; }

"="           { std::cout << "ASSIGN\n"; }
"{"           { std::cout << "LBRACE\n"; }
"}"           { std::cout << "RBRACE\n"; }

[a-zA-Z_][a-zA-Z0-9_]* {
                 std::cout << "IDENTIFIER: " << yytext << "\n";
               }

[ \t\r]+      ;   // ignore whitespace

\n            { line++; }

.             { std::cout << "INVALID: " << yytext << "\n"; }

%%

int yywrap() {
    return 1;
}
