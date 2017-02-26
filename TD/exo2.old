%{
    #include <stdio.h>
    #define false 0
    #define true 1

    void conj(int index);
    char term[6];
%}

pps je
dps tu
tps il|elle|on
ppp nous
dpp vous
tpp ils|elles 

%s spps sdps stps sppp sdpp stpp

%%
{pps} {BEGIN spps;}
{dps} {BEGIN sdps;}
{tps} {BEGIN stps;}
{ppp} {BEGIN sppp;}
{dpp} {BEGIN sdpp;}
{tpp} {BEGIN stpp;}

<spps>\[(.*)\] {}

. {ECHO;}
%%

term[0] = "e";
term[1] = "es";
term[2] = "e";
term[3] = "ons";
term[4] = "ez";
term[5] = "ent";

void conj(int index)
{
    printf("%s", term[index]);
}


int main( void ) {
    if(yylex() != 0)
    {
        return 1;
    }
   
}