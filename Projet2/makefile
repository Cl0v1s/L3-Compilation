int_pp: ppascal.l ppinterpret.y
	bison -d ppinterpret.y
	flex ppascal.l
	cc -o test/int_pp ppinterpret.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;



test: include/Variable.c include/Env.c include/Function.c include/test.c
	cc -o test/test include/*.c -DDEBUG


testStack: include/Variable.c include/Stack.c include/Env.c include/Function.c include/testStack.c
	cc -o test/stack include/*.c --DEBUG



