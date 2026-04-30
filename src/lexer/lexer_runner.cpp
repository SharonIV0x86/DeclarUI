#include <cstdio>
extern "C"
{
    extern FILE *yyin;
    extern FILE *yyout;
    int yylex();
}

void runLexer(const char *inputFile, const char *tokenFile)
{
    yyin = fopen(inputFile, "r");
    yyout = fopen(tokenFile, "w");

    if (!yyin || !yyout)
    {
        printf("Lexer error: cannot open file\n");
        return;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);
}