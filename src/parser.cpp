#include "parser.h"

static std::deque<unsigned char> Deque;
static std::map<std::string, unsigned char>  Variables;

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
    Variables[VarName] = 0;
  }

  switch(ArithOp) {
    case tok_decrement: Variables[VarName]--; break;
    case tok_increment: Variables[VarName]++; break;
  }

  return 0;
}

/// assignment
///   ::= variable assignment numeric
///   ::= variable assignment variable
static ExprAST *ParseAssignment() {
  std::string VarSource;
  std::string VarName    = lastIdentifier();
  unsigned char VarValue = -1;

  getNextToken();

  if (tok_assign != CurTok) {
    return Error("Missing assignment after variable token");
  }

  getNextToken();

  VarSource = lastIdentifier();

  if (0 == strcmp("/dev/null", VarSource.c_str())) {
    VarValue = 0;
  } else if (tok_variable == CurTok) {
    if (!Variables[VarSource]) {
      VarValue = 0;
    } else {
      VarValue = Variables[VarSource];
    }
  } else {
    VarValue = lastValue();
  }

  Variables[VarName] = VarValue;

  return 0;
}

/// deque
///   ::= dequeue variable
///   ::= pop variable
///   ::= push variable
static ExprAST *ParseDeque() {
  int         DequeOp = CurTok;
  std::string VarName;

  getNextToken();

  if (tok_variable != CurTok) {
    return Error("Missing variable name for deque");
  }

  VarName = lastIdentifier();

  switch(DequeOp) {
    case tok_dequeue:
      if (Deque.empty()) {
        Variables[VarName] = 0;
      } else {
        Variables[VarName] = Deque.front();
        Deque.pop_front();
      }
      break;

    case tok_pop:
      if (Deque.empty()) {
        Variables[VarName] = 0;
      } else {
        Variables[VarName] = Deque.back();
        Deque.pop_back();
      }
      break;

    case tok_push:
      if (!Variables[VarName]) {
        Deque.push_back(0);
      } else {
        Deque.push_back(Variables[VarName]);
      }
      break;
  }

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

  fprintf(stdout, "%c", Variables[VarName]);

  return 0;
}

/// sleepexpr
///   ::= sleep variable
static ExprAST *ParseSleep() {
  std::string VarName;

  getNextToken();

  if (tok_variable != CurTok) {
    return Error("Missing variable name for sleep");
  }

  VarName = lastIdentifier();

  if (!Variables[VarName]) {
    return Error("Unknown variable");
  }

  fflush(stderr);
  fflush(stdout);
  usleep((int) Variables[VarName] * 1000);

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

static void HandleDeque() {
  if (!ParseDeque()) {
    getNextToken();
  }
}

static void HandleOutput() {
  if (!ParseOutput()) {
    getNextToken();
  }
}

static void HandleSleep() {
  if (!ParseSleep()) {
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

      case tok_dequeue:
      case tok_pop:
      case tok_push:
        HandleDeque();
        break;

      case tok_output:
        HandleOutput();
        break;

      case tok_sleep:
        HandleSleep();
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
