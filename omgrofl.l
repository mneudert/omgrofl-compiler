%{
    #include <cstdio>
    #include <iostream>
    #include "omgrofl.tab.h"

    #define YY_DECL extern "C" int yylex()
%}

%option case-insensitive

%x COMMENT

%%
#!\/.+\/omgrofl /* ignore shebang */;
[ \t]+          /* ignore whitespace */;
\n              { return ENDL; }

l[o]+l          { yylval.var = new std::string(yytext); return VARIABLE; }
2[0-5][0-5]     { yylval.val = atoi(yytext); return VALUE; }
1[0-9][0-9]     { yylval.val = atoi(yytext); return VALUE; }
[1-9][0-9]      { yylval.val = atoi(yytext); return VALUE; }
[0-9]           { yylval.val = atoi(yytext); return VALUE; }
\/dev\/null     { yylval.val = atoi(yytext); return VALUE; }

(iz|to)         { return ASSIGN; }
lmao            { return LMAO; }
rofl            { return ROFL; }
roflmao         { return ROFLMAO; }
stfu            { return STFU; }

w00t            { BEGIN(COMMENT); }
<COMMENT>\n     { BEGIN(INITIAL); }
<COMMENT>.      /* ignore comments */;

.               /* hide everything -> yyerror() */;
%%
