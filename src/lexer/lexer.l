%option noyywrap

%{
#include <stdio.h>
#include <string.h>

int line = 1;
%}

/* Rules */
%%
"Window"      { fprintf(yyout, "WINDOW\t-\t%d\n", line); }
"Button"      { fprintf(yyout, "BUTTON\t-\t%d\n", line); }
"Label"       { fprintf(yyout, "LABEL\t-\t%d\n", line); }
"TextField"   { fprintf(yyout, "TEXTFIELD\t-\t%d\n", line); }
"VBox"        { fprintf(yyout, "VBOX\t-\t%d\n", line); }
"HBox"        { fprintf(yyout, "HBOX\t-\t%d\n", line); }

[0-9]+        { fprintf(yyout, "NUMBER\t%s\t%d\n", yytext, line); }

\"([^"]*)\"   {
    int len = yyleng;
    if (len >= 2) {
        fprintf(yyout, "STRING\t%.*s\t%d\n", len-2, yytext+1, line);
    } else {
        fprintf(yyout, "STRING\t\t%d\n", line);
    }
}
"="           { fprintf(yyout, "ASSIGN\t=\t%d\n", line); }
"{"           { fprintf(yyout, "LBRACE\t{\t%d\n", line); }
"}"           { fprintf(yyout, "RBRACE\t}\t%d\n", line); }

[a-zA-Z_][a-zA-Z0-9_]* { fprintf(yyout, "IDENTIFIER\t%s\t%d\n", yytext, line); }

[ \t\r]+      ;   /* ignore whitespace */
\n            { line++; }

.             { fprintf(yyout, "INVALID\t%.*s\t%d\n", yyleng, yytext, line); }
%%