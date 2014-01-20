#include "parser.hpp"

static std::map<std::string, unsigned char> Variables;

static int CurTok;
int getNextToken() {
  return CurTok = gettok();
}

ExprAST *Error(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return 0;
}

static ExprAST *ParseExpression();


/// arithmetic
///   ::= increment variable
///   ::= decrement variable
static ExprAST *ParseArithmetic() {
  int         ArithOp = CurTok;
  std::string VarName;

  getNextToken();

  if (tok_variable != CurTok) {
    return Error("Missing variable name for arithmetic");
  }

  VarName = lastIdentifier();

  if (!Variables[VarName]) {
    return Error("Unknown variable");
  }

  switch(ArithOp) {
    case tok_decrement: Variables[VarName]--; break;
    case tok_increment: Variables[VarName]++; break;
  }

  return 0;
}

/// assignment
///   ::= variable assignment numeric
static ExprAST *ParseAssignment() {
  std::string VarName    = lastIdentifier();
  unsigned char VarValue = -1;

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

  Variables[VarName] = VarValue;

  return 0;
}

/// identifierexpr
///   ::= identifier
static ExprAST *ParseIdentifierExpr() {
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

/// outputexpr
///   ::= output variable
static ExprAST *ParseOutput() {
  std::string VarName;

  getNextToken();

  if (tok_variable != CurTok) {
    return Error("Missing variable name for output");
  }

  VarName = lastIdentifier();

  if (!Variables[VarName]) {
    return Error("Unknown variable");
  }

  fprintf(stdout, "%s", &Variables[VarName]);

  return 0;
}


static void HandleArithmetic() {
  if (!ParseArithmetic()) {
    getNextToken();
  }
}

static void HandleAssignment() {
  if (!ParseAssignment()) {
    getNextToken();
  }
}

static void HandleOutput() {
  if (!ParseOutput()) {
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  if (!ParseExpression()) {
    getNextToken();
  }
}


/// top ::= definition | external | expression | ';'
void MainLoop() {
  while (1) {
    if (tok_eol == CurTok && isReplMode()) {
      fprintf(stdout, "\n>> ");
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
        return;

      case tok_increment:
      case tok_decrement:
        HandleArithmetic();
        break;

      case tok_output:
        HandleOutput();
        break;

      case tok_variable:
        HandleAssignment();
        break;

      default:
        HandleTopLevelExpression();
        break;
    }
  }
}
