/* recognize tokens for the calculator and print them out */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ppinterpret.tab.h"
%}

%option yylineno

%%

"new" { return NewAr; }
"array of" { return T_ar; }
"integer" { return T_int; }
"boolean" { return T_boo; }
"defun" { return Def; }
"defpro" { return Dep; }
":=" { return Af; }
"true" { return True; }
"false" { return False; }
";" { return Se; }
"if" { return If; }
"then" { return Th; }
"else" { return El; }
"var" { return Var; }
"while" { return Wh; }
"do" { return Do; }
"+" { return Pl; }
"-" { return Mo; }
"*" { return Mu; }
"and" { return And; }
"or" { return Or; }
"not" { return Not; }
"<=" { return Lt; }
"=" { return Eq; }
"(" { return OPar; }
")" { return CPar; }
"[" { return OBracket; }
"]" { return CBracket; }
"{" { return OBrace; }
"}" { return CBrace; }
"," { return Comma; }
":" { return Colon; }
"    " { return SpaceTab; }

([1-9][0-9]*)|0 { yylval.constant = atoi(yytext); return I; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.identity = strdup(yytext); return V; }

[ \t] {;} //Ignore

. {;}

%%
