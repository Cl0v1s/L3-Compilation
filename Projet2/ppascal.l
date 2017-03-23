/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    // TODO : Include ppascal.tab.h
%}

%option yylineno

%%

"Pl" {return Pl;}
"Mo" {return Mo;}
"Mu" {return Mu;}
"Or" {return Af;}
"Lt" {return Afc;}
"Eq" {return Sk;}
"And" {return Jp;}
"Not" {return Jz;}
"true" {return St;}
"false" {return St;}
"(" {return Open;}
")" {return Close;}
 // TODO : Complete with the rest of the syntax. 
"-" {return Minus;}
"+" {return Plus;}

":" {return Sp;}
\n {return Se;}

([1-9][0-9]*)|0 {yylval.constant = atoi(yytext);return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.variable = strdup(yytext); return V; }

[ \t] {;} //Ignore

. {;}

%%
