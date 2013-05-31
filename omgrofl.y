%{
    #include <cstdio>
    #include <iostream>
    #include <map>
    #include "omgrofl.tab.h"

    extern "C" int yylex();
    extern "C" FILE *yyin;

    void yyerror(const char *s);

    static bool interactive = false;
    static std::map<std::string, char> vars;

    void prompt() {
        if (interactive) { std::cout << "> "; }
    }
%}

%token ASSIGN
%token ENDL
%token LMAO
%token ROFL
%token ROFLMAO
%token STFU

%union {
    std::string *var;
    char val;
}

%token <val> VALUE
%token <var> VARIABLE

%%

omgrofl:
    | command omgrofl
    ;

command:
    error { yyclearin; yyerrok; }
    | STFU { return 0; }
    | VARIABLE ASSIGN VALUE ENDL { vars[*$1] = $3; prompt(); }
    | LMAO VARIABLE ENDL { vars[*$2]++; prompt(); }
    | ROFL VARIABLE ENDL { interactive
                             ? std::cout << vars[*$2] << std::endl
                             : std::cout << vars[*$2];
                           prompt(); }
    | ROFLMAO VARIABLE ENDL { vars[*$2]--; prompt(); }
    ;

%%

main(int argc, char **argv) {
    ++argv, --argc; // skip program name

    if (0 < argc) {
        yyin = fopen(argv[0], "r");
    } else {
        interactive = true;
        yyin = stdin;
    }

    prompt();
    yyparse();
}

/**
 * Catches "single" errors.
 *
 * Details: @see http://publib.boulder.ibm.com/infocenter/zvm/v5r4/index.jsp?topic=/com.ibm.zvm.v54.dmsp4/hcsp4b10106.htm
 */
void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;

    interactive ? prompt() : exit(1);
}
