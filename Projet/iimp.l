/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "iimp.tab.h"
    /*enum yytokentype 
    {
        V = 258,
        I = 259,
        AF = 260,
        SK = 261,
        SE = 262,
        IF = 263,
        TH = 264,
        EL = 265,
        WH = 266,
        DO = 267,
        PL = 268,
        MO = 269,
        MU = 270,
        OPEN = 271,
        CLOSE = 272,
        EOL = 273,
    };
    int yylval;*/
%}

%option yylineno

%%



"Af" { return AF; }
"Sk" { return SK; }
"Se" { return SE; }
"If" { return IF; }
"Th" { return TH; }
"El" { return EL; }
"Wh" { return WH; }
"Do" { return DO; }
"Pl" { return PL; }
"Mo" { return MO; }
"Mu" { return MU; }
"(" { return OPEN; }
")" { return CLOSE; }

([1-9][0-9]*)|0 {yylval = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { return V; }

%%

/*int main(int argc, char **argv)
{
    int tok;
    while(tok = yylex())
    {
        if(tok == I)
        {
            printf(" = %d\n", yylval);
        }
        else if(tok == V)
        {
            printf("var '%s'\n", yytext);
        }
        else 
            printf("%d\n", tok);
    }
}*/