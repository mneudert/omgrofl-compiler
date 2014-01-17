#include "lexer.hpp"

static std::string IdentifierStr;

int gettok() {
  static int LastChar = ' ';

  // skip whitespace
  while (isspace(LastChar)) {
    LastChar = getchar();
  }

  // get command / identifier
  if (isalnum(LastChar)) {
    IdentifierStr = LastChar;

    while (isalnum((LastChar = getchar()))) {
      IdentifierStr += LastChar;
    }

    if (IdentifierStr == "stfu") {
      return tok_eof;
    }

    return tok_identifier;
  }

  // catch end-of-file
  if (LastChar == EOF) {
    return tok_eof;
  }

  int ThisChar = LastChar;
  LastChar     = getchar();

  return ThisChar;
}

std::string lastIdentifier() {
  return IdentifierStr;
}
