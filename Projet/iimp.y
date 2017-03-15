%{
	/*
		# Projet de compilation 

		Réalisé par: Célia Paqué et Clovis Portron  
		Les fichiers produits avec make se trouvent dans le répertoire test/.

		# Question 1:
			Fonction C répondant à la question: int main();  
			Dans les fichiers: (produite à partir de) iimp.l et iimp.y  
			Compilation avec: make int_imp

		# Question 2:
			Fonction C répondant à la question: int main();
			Dans les fichiers: (produite à partir de) c3a.l et c3a.y  
			Compilation avec: make int_c3a

		# Question 3:
			Fonction C répondant à la question: int main();
			Dans les fichiers: (produite à partir de) comp_imp.l et comp_imp.y  
			Compilation avec: make comp_imp

		# Question 4:
			Fonction C répondant à la question: int main();
			Dans les fichiers: (produite à partir de) comp_c3a.l et comp_c3a.y  
			Compilation avec: make comp_c3a

		# Commande iimp:
			Compilée avec: make iimp
			Située dans test/
	*/


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
	 		Env env;
			Env_init(&env);
			Ast_IMP_run($1, &env);
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