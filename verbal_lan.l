%{
#include <stdio.h>
#include "parser_lan.tab.h"

int line_num = 1;
%}

%%

/* Keywords */
"bazinga"   {return PRINT;} /* Εμφάνιση μυνήματος */
"empower"   {return EMPOWER;} /* Ύψωση του αριθμού στην δύναμη */
"box"   {return BOX;} /* Ύψωση του αριθμού στο τετράγωνo */

/* Integers */
[0-9]+  {return INT_LITERAL;}

/* Identifiers
Κανόνας: Πρέπει να ξεκινάει αναγκαστικά με κεφαλαιο γράμμα και να τελιώνει με @ */
[A-Z][a-zA-Z0-9]*@    {return IDENTIFIER;} 

/* Operators and Symblols */
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"=" {return '=';}
";" {return ';';}
"," {return ',';}
"(" {return '(';}
")" {return ')';}

"\\bye" { line_num++; } /* Για να αυξήσουμε τον μετρητή γραμμών */
[ \t]+    {/* Για να αγνοούμε τα κενά και tabs*/}
"MINE#".* { /* Για την εισαγωγή σχόλιων */ }

/* Error Handler */
.   {printf("ΛΑΘΟΣ! ΛΑΘΟΣ! ΕΝΤΟΠΙΣΤΗΚΕ ΑΓΝΩΣΤΟΣ ΧΑΡΑΚΤΗΡΑΣ '%s' στην γραμμή %d\n", yytext, line_num);}

 %% 

 int yywrap() {
    return 1;
}
