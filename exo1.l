%{
    #include <stdio.h>
    #define false 0
    #define true 1
    char find = false;
    int position = 0;

    void matched();
%}

%%
[^abc\s\n\t]    {printf("%s Not {a,b,c} !\n", yytext); return 1;}
cabb             {matched(0);}
cbab             {matched(1);}
cbb             {matched(2);}
cbbba             {matched(3);}
. {position++;}
%%
void matched(int match)
{
    printf("(%d, %d)", position, match);
    position++;
    find = true;
    yyless(position);
}

int main( void ) {
    if(yylex() == 1)
    {
        return;
    }
    if(find == true)
        printf("Trouvé\n");
    else 
        printf("NOPE\n");
}