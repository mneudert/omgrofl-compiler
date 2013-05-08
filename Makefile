CPP = g++
INSTALL = install
LEX = flex
PREFIX = /usr
YACC = bison

.PHONY: all

all:
	$(YACC) -d omgrofl.y
	$(LEX) omgrofl.l
	$(CPP) omgrofl.tab.c lex.yy.c -o omgrofl -lfl

clean:
	$(RM) lex.yy.c omgrofl.tab.c omgrofl.tab.h

install:
	-test ! -f omgrofl || $(INSTALL) -m 0755 omgrofl $(PREFIX)/bin