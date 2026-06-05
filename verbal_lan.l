%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_lan.tab.h"

int line_num = 1;
%}

%%

"\\bye"              { return BYE; }
"bazinga"           { return PRINT; }
"empower"           { return EMPOWER; }
"box"               { return BOX; }

[0-9]+              { yylval.number = atoi(yytext); return INT_LITERAL; }

[A-Z][a-zA-Z0-9]*@  { yylval.str = strdup(yytext); return IDENTIFIER; }

\"[^\"]*\"          { yylval.str = strdup(yytext); return STRING_LITERAL; }

"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"=" { return '='; }
";" { return ';'; }
"," { return ','; }
"(" { return '('; }
")" { return ')'; }

[ \t\r]+              { /* Αγνοούμε τα κενά και τα tabs */ }
\n                    {line_num++;}
"MINE#".* { /* Αγνοούμε τα σχόλια */ }



%%

int yywrap() {
    return 1;
}
