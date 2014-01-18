#include <cstdio>
#include <string>
#include "ast.hpp"
#include "lexer.hpp"
#include "logger.hpp"

#ifndef __PARSER_H
#define __PARSER_H

int getNextToken();
void MainLoop();

#endif
