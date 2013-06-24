compiler: yacc c_lex
	g++ lex.o yacc.cc -o compiler

c_lex: lex
	gcc -c lex.yy.c -o lex.o

yacc: pl0.y
	yacc -d pl0.y -o yacc.cc

lex: pl0.l
	lex pl0.l
