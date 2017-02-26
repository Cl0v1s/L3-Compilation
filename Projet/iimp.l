/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
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

"Af" { return Af; }
"Sk" { return Sk; }
"Se" { return Se; }
"If" { return If; }
"Th" { return Th; }
"El" { return El; }
"Wh" { return Wh; }
"Do" { return Do; }
"Pl" { return Pl; }
"Mo" { return Mo; }
"Mu" { return Mu; }

([1-9][0-9]*)|0 {yylval.constant = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.variable = strdup(yytext); return V; }

%%
