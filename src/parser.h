#ifndef PARSER_H_
#define PARSER_H_

#include <unistd.h>
#include <cstdio>
#include <deque>
#include <string>

#include "./ast.h"
#include "./lexer.h"


int getNextToken();
void MainLoop();

#endif  // PARSER_H_
