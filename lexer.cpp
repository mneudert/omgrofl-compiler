#include "lexer.hpp"

static char* FileContent;
static int   FileContentPos = 0;
static bool  IsReplMode     = true;

static std::string IdentifierStr;
static unsigned char NumVal;
static std::map<std::string, Token> IdentifierMap;

bool isReplMode() {
  return IsReplMode;
}

void setFileMode(char* content) {
  FileContent = content;
  IsReplMode  = false;
}

int getCodeChar() {
  if (IsReplMode) {
    return tolower(getchar());
  } else {
    if (!FileContent[FileContentPos + 1]) {
      return -1;
    }

    return tolower(FileContent[FileContentPos++]);
  }
}

int gettok() {
  static int LastChar = ' ';
  bool isVariable     = false;

  if (IdentifierMap.empty()) {
    initIdentifiers();
  }

  // skip whitespace
  while (isspace(LastChar) && '\n' != LastChar) {
    LastChar = getCodeChar();
  }

  // ignore possible shebang lines
  if ('#' == LastChar) {
    std::string BangStr;

    do {
      BangStr += LastChar;
      LastChar = getCodeChar();
    } while (!isspace(LastChar));

    if ((10 > BangStr.size()) ||
        (0 != BangStr.compare(0, 3, std::string("#!/"))) ||
        (0 != BangStr.compare(BangStr.size() - 7, 7, std::string("omgrofl"))))
    {
      IdentifierStr = BangStr;
      return tok_identifier;
    }

    return tok_comment;
  }

  // get command / identifier
  if (isalpha(LastChar) || '/' == LastChar) {
    IdentifierStr = LastChar;

    if ('l' == LastChar) {
      isVariable = true;
    }

    while (isalnum((LastChar = getCodeChar())) || '/' == LastChar) {
      if ('l' != LastChar && 'o' != LastChar) {
        isVariable = false;
      }

      IdentifierStr += LastChar;
    }

    if (isVariable && (3 <= IdentifierStr.size()) &&
        (0 == IdentifierStr.compare(0, 1, std::string("l"))) &&
        (0 == IdentifierStr.compare(IdentifierStr.size() - 1, 1, std::string("l")))) {
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
      LastChar = getCodeChar();
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
  LastChar     = getCodeChar();

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
  IdentifierMap["afk"]     = tok_sleep;
  IdentifierMap["iz"]      = tok_assign;
  IdentifierMap["lmao"]    = tok_increment;
  IdentifierMap["rofl"]    = tok_output;
  IdentifierMap["roflmao"] = tok_decrement;
  IdentifierMap["stfu"]    = tok_eof;
  IdentifierMap["to"]      = tok_assign;
  IdentifierMap["w00t"]    = tok_comment;
}
