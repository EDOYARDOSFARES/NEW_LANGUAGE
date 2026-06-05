%{
#include <stdio.h>
#include "parser.tab.h"

int line_num = 1;
%}

%%

/* Keywords */
"bazinga"   {return PRINT;}

/* Integers */
[0-9]+  {return INT_LITERAL;}

/* Identifiers
Κανόνας: Πρέπει να ξεκινάει αναγκαστικά με κεφαλαιο γράμμα και να τελιώνει με @ */
[A-Z][a-zA-Z0-9]*@    {return IDENTIFIER;} 

/* Operators and Symblols */
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
"=" {return EQUAL;}
";" {return SEMICOLON;}
"," {return COMMA;}
"(" {return LPAREN;}
")" {return RPAREN;}

"\\bye" { line_num++; } /* Για να αυξήσουμε τον μετρητή γραμμών */
[ \t]+    {/* Για να αγνοούμε τα κενά και tabs/*}

/* Error Handler */
.   {printf("ΛΑΘΟΣ! ΛΑΘΟΣ! ΕΝΤΟΠΙΣΤΗΚΕ ΑΓΝΩΣΤΟΣ ΧΑΡΑΚΤΗΡΑΣ '%s' στην γραμμή %d\n", yytext, line_num);}

 %% 

 int yywrap() {
    return 1;
}
