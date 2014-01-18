#include "logger.hpp"

static bool verbose = false;

void log(const char* format, ...) {
  va_list argptr;

  if (!verbose) {
    return;
  }

  va_start(argptr, format);
  vfprintf(stdout, format, argptr);
  va_end(argptr);
}

void setVerbose() {
  verbose = true;
}
