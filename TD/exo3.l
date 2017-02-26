%{
    #include <stdio.h>


    #include "include/Dict.h"
    #include "include/Types.h"

    Dict types;
    char* current_exp;

%}

instruction while|do
operators :=|\+|;|\*|" "
esp " "|\t|\n

%s VAR

%%

{instruction} {}
{operators} {}

.*\s*/{esp} {
    current_exp = malloc(strlen(yytext));
    strcpy(current_exp, yytext);
    BEGIN VAR;}
<VAR>[0-9]* {
    if(Dict_key_exists(&types, current_exp))
    {

    }
    Dict_set_value(&types, current_exp, INT);
    ;BEGIN INITIAL;}

. {}

%%





int main( void ) {
    Dict_init(&types);

    if(yylex() != 0)
    {
        return 1;
    }

    Dict_print(&types);

   
}