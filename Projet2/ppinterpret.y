%{
	#include <stdio.h>
	#include <string.h>
	#include "include/Function.h"
	#include "include/Variable.h"
	#include "include/Env.h"
    #include "include/Ast.h"
    #include "include/Pascal.h"
    #include "include/Stack.h"

	int yyerror(char *s);
	int yylex();
	int yylineno;

	struct Stack* stack;
%}

	%union {
		char* identity;
		int constant;
        struct Type* type;
        struct Variable* variable;
        struct Env* env;
        struct FuncDisclaimer* funcDisc;
        struct Func* function;
        struct FuncList* funcList;
        struct Ast*  ast;
	}

	%token<identity>V
	%token<constant>I
	%token NFon NPro NewAr Sk T_ar T_boo T_int Def Dep Af True False Se If Th El Var Wh Do Pl Mo Mu And Or Not Lt Eq OPar CPar OBracket CBracket OBrace CBrace Comma Colon SpaceTab

	%start MP

  %type<type> TP

  %type<env> L_argt L_argtnn Argt L_vartnn L_vart
  %type<funcDisc> D_entf D_entp
  %type<funcList> LD
   %type<function> D
  %type<ast> E Et C CC L_argsnn L_args


    %left Se
    %left Pl Mo
	%left Mu
	%left OPar OBracket



%%


MP: L_vart LD C {
    Pascal_semanticFunctions($2);
    Pascal_semanticAnalyse(Stack_clone(stack), Env_concat($1, 0), $2 , $3, 0);
    Pascal_run(stack, $1, $2, $3, 0);
    Stack_print(stack);
    printf("\nSORTIE\n");
    Env_print($1, stack);
}

E: E Pl E { $$ = Ast_init('E', Pl, $1, $3); }
  | E Mo E { $$ = Ast_init('E', Mo, $1, $3); }
  | E Mu E { $$ = Ast_init('E', Mu, $1, $3); }
  | E Or E { $$ = Ast_init('E', Or, $1, $3); }
  | E Lt E { $$ = Ast_init('E', Lt, $1, $3); }
  | E Eq E { $$ = Ast_init('E', Eq, $1, $3); }
  | E And E { $$ = Ast_init('E', And, $1, $3); }
  | Not E { $$ = Ast_init('E', Not, $2, 0); }
  | OPar E CPar { $$ = $2; }
  | I { $$ = Ast_init_leaf_const('I', $1); }
  | Mo I { $2 = $2 * -1; $$ = Ast_init_leaf_const('I', $2); }
  | V { $$ = Ast_init_leaf_ptr('V', $1); }
  | True { $$ = Ast_init_leaf_const('B', true); }
  | False { $$ = Ast_init_leaf_const('B', false); }
  | V OPar L_args CPar { $$ = Ast_init('E', CallFUNC, Ast_init_leaf_ptr('V', $1), $3); }
  | NewAr TP OBracket E CBracket { $$ = Ast_init('E', NewAr, Ast_init_leaf_ptr('T', $2), $4); }
  | Et { $$=$1; }

Et: V OBracket E CBracket { $$ = Ast_init('E', GetARR, Ast_init_leaf_ptr('V', $1), $3); }
  | Et OBracket E CBracket { $$ = Ast_init('E', GetARR, $1, $3); }

CC: Et Af E { $$ = Ast_init('C', AfInd, $1, $3); }
  | V Af E { $$ = Ast_init('C', Af, Ast_init_leaf_ptr('V', $1), $3); }
  | Sk { $$ = Ast_init('C', Sk, 0,0); }
  | OBrace C CBrace { $$ = $2; }
  | If E Th C El CC { $$ = Ast_init('C', If, $2, Ast_init('C', El, $4, $6));}
  | Wh E Do CC { $$ = Ast_init('C', Wh, $2, $4); }
  | V OPar L_args CPar { $$ = Ast_init('C', CallFUNC, Ast_init_leaf_ptr('V', $1), $3); }

C :  C Se CC { $$ = Ast_init('C', Se, $1, $3);}
   | CC {$$ = $1;}

L_args: %empty { $$ = Ast_init('L', 0, 0, 0); }
  | L_argsnn { $$ = $1;}

L_argsnn: E { $$ = Ast_init('L', 0, 0, $1); }
  | E Comma L_argsnn { $$ = Ast_init('L', 0, $3, $1); }

L_argt: %empty { $$ = Env_init(); }
  | L_argtnn { $$ = $1;}

L_argtnn: Argt { $$ = $1;}
  | L_argtnn Comma Argt { $$ = Env_concat($1, $3);free($1); free($3); }

Argt: V Colon TP { $$ = Env_init(); Env_set_value($$, $1,Variable_arrayInit(stack, $3, 1)); }

TP: T_boo { $$ = Type_init(BOOL, 0); }
  | T_int  { $$ = Type_init(INT, 0); }
  | T_ar TP { $$ = Type_init(ARRAY, $2); }

L_vart: %empty {  $$ = Env_init(); }
  | L_vartnn { $$ = $1;}

L_vartnn: Var Argt { $$ = $2; }
  | L_vartnn Comma Var Argt { $$ = Env_concat($1, $4); free($1); free($4); }

D_entp: Dep V OPar L_argt CPar { $$ = FuncDisclaimer_init($2, $4, Type_init(VOID, 0)); }

D_entf: Def V OPar L_argt CPar Colon TP { $$ = FuncDisclaimer_init($2, $4, $7); }

D: D_entp L_vart C { $$ = Func_init( $1, $2, $3); }
  | D_entf L_vart C { $$ = Func_init( $1, $2, $3); }

LD: %empty { $$ = FuncList_init(); }
  | LD D { FuncList_append($1, $2); }

%%

int main()
{
    stack = Stack_init();
	yyparse();
}


int yyerror(char *s)
{
 fprintf(stderr, "error: %s near %d\n", s, yylineno);
}
