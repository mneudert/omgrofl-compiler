%{
    #include <stdio.h>
    #include "omgrofl.tab.h"

    extern "C"
    {
        int yylex(void);
    }
%}

%option case-insensitive

%%
[ \t]+    /* ignore whitespace */;
\n        { return ENDL; }

iz        { return ASSIGN; }
l[o]+l    { char *res = new char[strlen(yytext) + 1];
            strcpy(res, yytext);
            yylval.sval = res;
            return VARNAME; }

[0-9]+    { yylval.ival = atoi(yytext);
            return NUMBER; }
%%
