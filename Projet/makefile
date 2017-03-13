flex:
	flex -i *.l; gcc -Wall lex.yy.c -o test/iimp -lfl; 

iimp: iimp.l iimp.y
	bison -d iimp.y
	flex iimp.l
	cc -o test/iimp iimp.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

comp_iimp: comp_iimp.l comp_iimp.y
	bison -d comp_iimp.y
	flex comp_iimp.l
	cc -o test/comp_iimp comp_iimp.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

c3a: c3a.l c3a.y
	bison -d c3a.y
	flex c3a.l
	cc -o test/c3a c3a.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

prepare: iimp.l iimp.y c3a.l c3a.y
	bison -d iimp.y
	flex iimp.l
	mv lex.yy.c iimp.yy.c
	cc -o test/iimp iimp.tab.c iimp.yy.c include/*.c -lfl
	bison -d c3a.y
	flex c3a.l
	mv lex.yy.c c3a.yy.c
	cc -o test/c3a c3a.tab.c c3a.yy.c include/*.c -lfl
