#include <errno.h>
#include <string>

#include "./lexer.h"
#include "./parser.h"


void parseFile(char *filename) {
  std::string omgcode;
  FILE        *fp;
  ssize_t     read;

  char    *line = NULL;
  size_t  len   = 0;

  fp = fopen(filename, "r");

  if (NULL == fp) {
    fprintf(stderr, "Failed to open file '%s': %s!\n",
                    filename, strerror(errno));
    exit(1);
  }

  while (-1 != (read = getline(&line, &len, fp))) {
    omgcode.append(std::string(line));
  }

  fclose(fp);
  setFileMode(omgcode);

  if (line) {
    free(line);
  }
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
