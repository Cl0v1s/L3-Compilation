all:
	flex *.l; gcc -Wall lex.yy.c -o main -lfl; rm -f *.c;