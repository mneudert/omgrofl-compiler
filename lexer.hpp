#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>

#ifndef __LEXER_H
#define __LEXER_H

enum Token {
  tok_eof        = -1,
  tok_eol        = -2,
  tok_assign     = -3,
  tok_comment    = -4,
  tok_identifier = -5,
  tok_numeric    = -6,
  tok_variable   = -7
};

int gettok();
std::string lastIdentifier();
int lastValue();

void initIdentifiers();

#endif
