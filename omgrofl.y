%{
    #include <stdio.h>

    void yyerror(const char *s)
    {
        fprintf(stderr, "error: %s\n", s);
    }

    extern "C"
    {
        int yyparse(void);
        int yylex(void);
        int yywrap()
        {
            return 1;
        }
    }
%}

%token ASSIGN
%token ENDL
%token STFU

%union {
    char *sval;
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
    | VARNAME ASSIGN NUMBER ENDL { printf("Variable '%s' assigned to '%d'\n", $1, $3); }
    ;

%%

main(int argc, char **argv)
{
    yyparse();
}