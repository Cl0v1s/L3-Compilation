all:
	flex -i *.l; gcc -Wall lex.yy.c -o main -lfl; rm -f *.c;