/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "c3a.tab.h"
%}

%option yylineno

%%

"Pl" {return Pl;}
"Mo" {return Mo;}
"Mu" {return Mu;}
"Af" {return Af;}
"Afc" {return Afc;}
"Sk" {return Sk;}
"Jp" {return Jp;}
"Jz" {return Jz;}
"St" {return St;}
"(" {return Open;}
")" {return Close;}
"-" {return Minus;}
"+" {return Plus;}

":" {return Sp;}
\n {return Se;}

([1-9][0-9]*)|0 {yylval.constant = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.variable = strdup(yytext); return V; }

[ \t] {;} //Ignore

. {;}

%%
