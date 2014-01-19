#include <cstdio>
#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "logger.hpp"
#include "parser.hpp"

using namespace std;

static bool verbose = false;

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

    delete[] omgcode;
  } else {
    fprintf(stderr, "Failed to open file!");
    return;
  }

  setFileMode(omgcode);
}

int main(int argc, char *argv[]) {
  // set verbosity
  if (2 <= argc) {
    if (0 == strcmp("-v", argv[1]) || 0 == strcmp("--verbose", argv[1])) {
      setVerbose();
      log("[ verbose mode! ]\n");
    }
  }

  // parse file
  if (2 <= argc) {
    if (0 != strcmp("-v", argv[argc - 1]) || 0 != strcmp("--verbose", argv[argc - 1])) {
      parseFile(argv[argc - 1]);
    }
  }

  // repl
  if (isReplMode()) { fprintf(stdout, ">> "); }

  getNextToken();
  MainLoop();

  return 0;
}
