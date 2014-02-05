INSTALL = install

.PHONY: all

all:
	$(CXX) -o omgrofl -g -O3 *.cpp

clean:
	rm -f omgrofl

install:
	test ! -f omgrofl || $(INSTALL) -m 0755 omgrofl $(PREFIX)/bin
