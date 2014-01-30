#include <cstdio>
#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

using namespace std;

void parseFile(char *filename) {
  streampos  size;
  char      *omgcode;

  ifstream file(filename, ios::in|ios::binary|ios::ate);

  if (file.is_open()) {
    size    = file.tellg();
    omgcode = new char[size];

    file.seekg(0, ios::beg);
    file.read(omgcode, size);
    file.close();
  } else {
    fprintf(stderr, "Failed to open file!");
    return;
  }

  setFileMode(omgcode);
}

int main(int argc, char *argv[]) {
  // parse file
  if (2 == argc) {
    parseFile(argv[1]);
  }

  // repl
  if (isReplMode()) { fprintf(stdout, ">> "); }

  getNextToken();
  MainLoop();

  return 0;
}
