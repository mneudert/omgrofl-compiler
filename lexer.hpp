#include <cctype>
#include <cstdio>
#include <string>

#ifndef __LEXER_H
#define __LEXER_H

enum Token {
  tok_eof        = -1,
  tok_identifier = -2
};

int gettok();
std::string lastIdentifier();

#endif
