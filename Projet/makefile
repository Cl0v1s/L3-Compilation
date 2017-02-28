flex:
	flex -i *.l; gcc -Wall lex.yy.c -o test/iimp -lfl; 

iimp: iimp.l iimp.y
	bison -d iimp.y
	flex iimp.l
	cc -o test/iimp iimp.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

c3a: c3a.l c3a.y
	bison -d c3a.y
	flex c3a.l
	cc -o test/c3a c3a.tab.c lex.yy.c include/*.c -lfl
	rm *.c;