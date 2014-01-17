#include <cstdio>
#include "parser.hpp"

int main() {
  fprintf(stdout, ">> ");
  getNextToken();

  MainLoop();

  return 0;
}
