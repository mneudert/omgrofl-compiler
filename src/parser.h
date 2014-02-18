#ifndef __PARSER_H
#define __PARSER_H

#include <cstdio>
#include <deque>
#include <string>
#include <unistd.h>
#include "ast.h"
#include "lexer.h"


int getNextToken();
void MainLoop();

#endif
