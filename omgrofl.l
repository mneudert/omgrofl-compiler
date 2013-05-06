%{
    #include <cstdio>
    #include <iostream>
    using namespace std;
    #define YY_DECL extern "C" int yylex()

    #include "omgrofl.tab.h"
%}

%option case-insensitive

%x COMMENT

%%
[ \t]+          /* ignore whitespace */;
\n              { return ENDL; }

iz              { return IZ; }
l[o]+l          { yylval.sval = new std::string(yytext); return VARNAME; }
[0-9]+          { yylval.ival = strtol(yytext, NULL, 10); return NUMBER; }
rofl            { return ROFL; }

stfu            { return STFU; }

w00t            { BEGIN(COMMENT); }
<COMMENT>\n     { BEGIN(INITIAL); }
<COMMENT>.      /* ignore comments */;

%%
