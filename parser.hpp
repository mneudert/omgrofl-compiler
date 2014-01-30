#include <cstdio>
#include <string>
#include <unistd.h>
#include "ast.hpp"
#include "lexer.hpp"

#ifndef __PARSER_H
#define __PARSER_H

int getNextToken();
void MainLoop();

#endif
