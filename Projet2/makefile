int_imp: iimp.l iimp.y
	bison -d iimp.y
	flex iimp.l
	cc -o test/int_imp iimp.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;

comp_imp: comp_iimp.l comp_iimp.y
	bison -d comp_iimp.y
	flex comp_iimp.l
	cc -o test/comp_imp comp_iimp.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

comp_c3a: comp_c3a.l comp_c3a.y
	bison -d comp_c3a.y
	flex comp_c3a.l
	cc -o test/comp_c3a comp_c3a.tab.c lex.yy.c include/*.c -lfl
	rm *.c;

int_c3a: c3a.l c3a.y
	bison -d c3a.y
	flex c3a.l
	cc -o test/int_c3a c3a.tab.c lex.yy.c include/*.c -lfl -DDEBUG
	rm *.c;

iimp: iimp/imp.c
	make comp_imp
	make comp_c3a
	cc -o test/iimp iimp/imp.c

test: include/Variable.c
	cc -o test/test include/*.c -DDEBUG
