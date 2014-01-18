#include <cstdio>
#include "logger.hpp"
#include "parser.hpp"

static bool verbose = false;

int main(int argc, char *argv[]) {
  if (2 <= argc) {
    if (0 == strcmp("-v", argv[1]) || 0 == strcmp("--verbose", argv[1])) {
      setVerbose();
      log("[ verbose mode! ]\n");
    }
  }

  fprintf(stdout, ">> ");
  getNextToken();

  MainLoop();

  return 0;
}
