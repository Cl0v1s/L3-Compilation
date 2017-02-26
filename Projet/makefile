flex:
	flex -i *.l; gcc -Wall lex.yy.c -o test/iimp -lfl; 

both: iimp.l iimp.y
	bison -d iimp.y
	flex iimp.l
	cc -o test/iimp iimp.tab.c lex.yy.c include/*.c -lfl
	rm -f *.c;