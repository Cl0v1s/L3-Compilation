/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "comp_iimp.tab.h"
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

":=" { return Af; }
"skip" { return Sk; }
";" { return Se; }
"if" { return If; }
"then" { return Th; }
"else" { return El; }
"while" { return Wh; }
"do" { return Do; }
"+" { return Pl; }
"-" { return Mo; }
"*" { return Mu; }
"(" { return Open; }
")" { return Close; }

([1-9][0-9]*)|0 {yylval.constant = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.variable = strdup(yytext); return V; }

[ \t\n] {;} //Ignore

. {;}

%%
