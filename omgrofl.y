%{
    #include <cstdio>
    #include <iostream>
    #include <map>
    #include "omgrofl.tab.h"

    extern "C" int yylex();
    extern "C" FILE *yyin;

    void yyerror(const char *s);

    static std::map<std::string, int> vars;
%}

%token ENDL
%token IZ
%token ROFL
%token STFU

%union {
    std::string *sval;
    int ival;
}

%token <ival> NUMBER
%token <sval> VARNAME

%%

omgrofl:
    | omgrofl command
    ;

command:
    STFU { return 0; }
    | VARNAME IZ NUMBER ENDL { vars[*$1] = $3; }
    | ROFL VARNAME ENDL { std::cout << "> " << vars[*$2] << std::endl; }
    ;

%%

main() {
    yyparse();
}

void yyerror(const char *s) {
    std::cout << "Parse error! Message: " << s << std::endl;
    exit(-1);
}
