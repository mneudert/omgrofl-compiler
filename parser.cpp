#include "parser.hpp"

static std::map<std::string, int> Variables;

static int CurTok;
int getNextToken() {
  return CurTok = gettok();
}

ExprAST *Error(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return 0;
}

static ExprAST *ParseExpression();


/// assignment
///   ::= variable assignment numeric
static ExprAST *ParseAssignment() {
  std::string VarName  = lastIdentifier();
  int         VarValue = -1;

  getNextToken();

  if (tok_assign != CurTok) {
    return Error("Missing assignment after variable token");
  }

  getNextToken();

  if (0 == strcmp("/dev/null", lastIdentifier().c_str())) {
    VarValue = 0;
  } else {
    VarValue = lastValue();
  }

  if (0 > VarValue) {
    return Error("Missing value after assignment token");
  }

  if (Variables[VarName]) {
    fprintf(stdout, "OldVal '%s': %d\n", VarName.c_str(), Variables[VarName]);
  }

  Variables[VarName] = VarValue;

  return 0;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static ExprAST *ParseIdentifierExpr() {
  fprintf(stderr, "Identifier: %s\n", lastIdentifier().c_str());

  return 0;
}

/// expression
///   ::= identifierexpr
static ExprAST *ParseExpression() {
  switch (CurTok) {
    case tok_identifier: return ParseIdentifierExpr();
    default: return Error("Unknown token when expecting an expression");
  }
}


static void HandleAssignment() {
  if (ParseAssignment()) {
    fprintf(stderr, "Variable assigned!\n");
  } else {
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  if (ParseExpression()) {
    fprintf(stderr, "Parsed a top-level expr!\n");
  } else {
    getNextToken();
  }
}


/// top ::= definition | external | expression | ';'
void MainLoop() {
  while (1) {
    if (tok_eol == CurTok) {
      fprintf(stdout, ">> ");
    }

    switch (CurTok) {
      case tok_eol:
        getNextToken();
        break;

      case tok_comment:
        // ignore comments
        while (tok_eol != CurTok) { getNextToken(); }
        break;

      case tok_eof:
        fprintf(stdout, "OmgEndOfFile!\n");
        return;

      case tok_variable:
        HandleAssignment();
        break;

      default:
        HandleTopLevelExpression();
        break;
    }
  }
}
