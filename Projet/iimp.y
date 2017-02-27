%{
	#include <stdio.h>
	#include "include/Ast.h"
	#include "include/IMP.h"
	#include "include/Env.h"	

	int yyerror(char *s);
	int yylex();
	int yylineno;
%}

	%union {
		int constant;
		char* variable;
		struct Ast *node;
	}
	%token<variable>V
	%token<constant>I
	%token Af Sk Se If Th Wh Do Pl Mo Mu
	%nonassoc Th
	%nonassoc El
	%left '('
	%start prog 

	/* %type<node> C0 C E T F*/
	%type<node> C E T F
	

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */ 
prog: C	{ 
	 		Env env;
			Env_init(&env);
			Ast_run($1, &env);
			Env_print(&env);
	 	}
    ;


E: E Pl T {$$ = Ast_init('E',Pl, $1, $3);}
| E Mo T {$$ = Ast_init('E',Mo, $1, $3);}
| T {$$ = $1;}
;

T: T Mu F {$$ = Ast_init('T',Mu,  $1, $3);}
| F {$$ = $1;}
;

F: '(' E ')' {$$ = $2;} 
| I	{$$ = Ast_init_leaf('I', &$1);}
| V {$$ = Ast_init_leaf('V', $1);}
;


C: V Af E {$$ = Ast_init('C', Af, Ast_init_leaf('V', $1), $3);}
| Sk {$$ = Ast_init('C', Sk, 0,0);}
| '(' C ')' {$$ = $2;}
| If E Th C El C {$$=Ast_init('C', If, $2, Ast_init('C', El, $4, $6));}
| Wh E Do C {$$=Ast_init('C', Wh, $2, $4);}
| C Se C { $$ = Ast_init('C', Se, $1, $3);}
;





%%

int main()
{
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}