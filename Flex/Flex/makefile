all: teste

list.o: list.c
	gcc -c list.c -o list.o

concepts.o: concepts.c 
	gcc -c concepts.c -o concepts.o

lex.o: lex.yy.c skos.l
	flex skos.l
	gcc -c lex.yy.c -o lex.o

teste: lex.o concepts.o list.o
	gcc lex.o concepts.o list.o -o teste -ll

