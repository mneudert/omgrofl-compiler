#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>

#ifndef __LEXER_H
#define __LEXER_H

enum Token {
  tok_eof        = -1,
  tok_eol        = -2,
  tok_comment    = -3,
  tok_identifier = -4
};

int gettok();
std::string lastIdentifier();

void initIdentifiers();

#endif
