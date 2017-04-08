/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "c3ainterpret.tab.h"
%}

%option yylineno

%%

"Lt" {return Lt;}
"Pl" {return Pl;}
"Mo" {return Mo;}
"Mu" {return Mu;}
"And" {return And;}
"Or" {return Or;}
"Not" {return Not;}
"Ind" {return Ind;}
"Af" {return Af;}
"Afc" {return Afc;}
"AfInd" {return AfInd;}
"Sk" {return Sk;}
"Jp" {return Jp;}
"Jz" {return Jz;}
"St" {return St;}
"Param" {return Param;}
"Call" {return Call;}
"Ret" {return Ret;}
"(" {return Open;}
")" {return Close;}
"-" {return Minus;}
"+" {return Plus;}

":" {return Sp;}
\n {return Se;}

([1-9][0-9]*)|0 {yylval.constant = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.identity = strdup(yytext); return V; }

[ \t] {;} //Ignore

. {;}

%%
