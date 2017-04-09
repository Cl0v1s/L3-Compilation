int_pp: ppascal.l ppinterpret.y
	bison -d ppinterpret.y
	flex ppascal.l
	cc -o test/int_pp ppinterpret.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;

comp_pp: ppascal.l pptoc3a.y
	bison -d pptoc3a.y
	mv pptoc3a.tab.h ppinterpret.tab.h
	mv pptoc3a.tab.c ppinterpret.tab.c
	flex ppascal.l
	cc -o test/comp_pp ppinterpret.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;

comp_pp_prod: ppascal.l pptoc3a.y
	bison -d pptoc3a.y
	mv pptoc3a.tab.h ppinterpret.tab.h
	mv pptoc3a.tab.c ppinterpret.tab.c
	flex ppascal.l
	cc -o test/comp_pp ppinterpret.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

int_c3a: c3a.l c3ainterpret.y
	bison -d c3ainterpret.y
	flex c3a.l
	cc -o test/int_c3a c3ainterpret.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;


test: include/Variable.c include/Env.c include/Function.c include/test.c
	cc -o test/test include/*.c -DDEBUG


testStack: include/Variable.c include/Stack.c include/Env.c include/Function.c include/testStack.c
	cc -o test/stack include/*.c --DEBUG



