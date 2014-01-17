#include "lexer.hpp"

static std::string IdentifierStr;
static std::map<std::string, Token> IdentifierMap;

int gettok() {
  static int LastChar = ' ';

  if (IdentifierMap.empty()) {
    initIdentifiers();
  }

  // skip whitespace
  while (isspace(LastChar) && '\n' != LastChar) {
    LastChar = getchar();
  }

  // get command / identifier
  if (isalnum(LastChar)) {
    IdentifierStr = LastChar;

    while (isalnum((LastChar = getchar()))) {
      IdentifierStr += LastChar;
    }

    if (IdentifierMap[IdentifierStr]) {
      return IdentifierMap[IdentifierStr];
    }

    return tok_identifier;
  }

  // catch end-of-file
  if (EOF == LastChar) {
    return tok_eof;
  }

  if ('\n' == LastChar) {
    LastChar = ' ';
    return tok_eol;
  }

  int ThisChar = LastChar;
  LastChar     = getchar();

  return ThisChar;
}

std::string lastIdentifier() {
  return IdentifierStr;
}

void initIdentifiers() {
  IdentifierMap["stfu"] = tok_eof;
  IdentifierMap["w00t"] = tok_comment;
}
