#ifndef LEXER_H_
#define LEXER_H_

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>


enum Token {
  tok_eof        = -11,
  tok_eol        = -12,
  tok_sleep      = -13,

  tok_assign     = -21,
  tok_comment    = -22,
  tok_identifier = -23,
  tok_numeric    = -24,
  tok_variable   = -25,

  tok_decrement  = -31,
  tok_increment  = -32,
  tok_output     = -33,

  tok_dequeue    = -41,
  tok_pop        = -42,
  tok_push       = -43
};

void setFileMode(std::string content);
bool isReplMode();

int gettok();
std::string lastIdentifier();
unsigned char lastValue();

void initIdentifiers();

#endif  // LEXER_H_
