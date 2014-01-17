#include "lexer.hpp"

static std::string IdentifierStr;
static unsigned char NumVal;
static std::map<std::string, Token> IdentifierMap;

int gettok() {
  static int LastChar = ' ';
  bool isVariable     = false;

  if (IdentifierMap.empty()) {
    initIdentifiers();
  }

  // skip whitespace
  while (isspace(LastChar) && '\n' != LastChar) {
    LastChar = getchar();
  }

  // get command / identifier
  if (isalpha(LastChar) || '/' == LastChar) {
    IdentifierStr = LastChar;

    if ('l' == LastChar) {
      isVariable = true;
    }

    while (isalnum((LastChar = getchar())) || '/' == LastChar) {
      if ('l' != LastChar && 'o' != LastChar && 'O' != LastChar) {
        isVariable = false;
      }

      IdentifierStr += LastChar;
    }

    if (isVariable && 'l' == IdentifierStr[IdentifierStr.length() - 1] && 3 >= IdentifierStr.length()) {
      return tok_variable;
    }

    if (IdentifierMap[IdentifierStr]) {
      return IdentifierMap[IdentifierStr];
    }

    return tok_identifier;
  }

  // get numeric values
  if (isdigit(LastChar)) {
    std::string NumStr;

    do {
      NumStr  += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar));

    NumVal = std::atoi(NumStr.c_str());

    return tok_numeric;
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
  std::string ident = IdentifierStr;
  IdentifierStr     = "";

  return ident;
}

unsigned char lastValue() {
  char value = NumVal;
  NumVal     = -1;

  return value;
}

void initIdentifiers() {
  IdentifierMap["iz"]   = tok_assign;
  IdentifierMap["rofl"] = tok_output;
  IdentifierMap["stfu"] = tok_eof;
  IdentifierMap["to"]   = tok_assign;
  IdentifierMap["w00t"] = tok_comment;
}
