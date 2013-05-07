CPP = g++
LEX = flex
YACC = bison

.PHONY: all

all:
	$(YACC) -d omgrofl.y
	$(LEX) omgrofl.l
	$(CPP) omgrofl.tab.c lex.yy.c -o omgrofl -lfl

clean:
	$(RM) lex.yy.c omgrofl.tab.c omgrofl.tab.h