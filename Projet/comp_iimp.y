%{
	#include <stdio.h>
	#include "include/IMP.h"
	#include "include/Ast.h"
	#include "include/Quads.h"
	#include "include/Comp_IMP.h"
	
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
	%token Af Sk Se If Th Wh Do Pl Mo Mu Open Close
	%start prog 

	%type<node> C E T F

	%nonassoc El Th

	%left Pl Mo
	%left Mu
	%left Open
	

%%

/* Un programme est une suite de déclaration (C) composé de déclaration atomique (C0) */ 
prog: C	{ 
			struct QuadList* compiled;
			IMP_Compile_C3A($1);
	 	}
    ;


E: E Pl T {$$ = Ast_init('E',Pl, $1, $3);}
| E Mo T {$$ = Ast_init('E',Mo, $1, $3);}
| T {$$ = $1;}
;

T: T Mu F {$$ = Ast_init('T',Mu,  $1, $3);}
| F {$$ = $1;}
;

F: Open E Close {$$ = $2;} 
| I	{$$ = Ast_IMP_init_leaf('I', &$1);}
| Mo I {$2 = $2 * (-1); $$ = Ast_IMP_init_leaf('I', &$2);}
| V {$$ = Ast_IMP_init_leaf('V', $1);}
;


C: V Af E {$$ = Ast_init('C', Af, Ast_IMP_init_leaf('V', $1), $3);}
| Sk {$$ = Ast_init('C', Sk, 0,0);}
| Open C Close {$$ = $2;}
| If E Th C El C {$$=Ast_init('C', If, $2, Ast_init('C', El, $4, $6));}
| Wh E Do C {$$=Ast_init('C', Wh, $2, $4);}
| C Se C { $$ = Ast_init('C', Se, $1, $3);}
| C Se { $$ = Ast_init('C', Se, $1, 0);}
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