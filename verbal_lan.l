%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_lan.tab.h"

int line_num = 1;
%}

%%

// Keywords 
"bazinga"   { return PRINT; } // Εμφάνιση μυνήματος 
"empower"   { return EMPOWER; } // Ύψωση του αριθμού στην δύναμη
"box"   { return BOX; } // Ύψωση του αριθμού στο τετράγωνo

// Integers 
[0-9]+              { yylval.number = atoi(yytext); return INT_LITERAL; }

/* Identifiers
Κανόνας: Πρέπει να ξεκινάει αναγκαστικά με κεφαλαιο γράμμα και να τελιώνει με @ */
[A-Z][a-zA-Z0-9]*@  { yylval.str = strdup(yytext); return IDENTIFIER; }

// Αναγνώριση στατικών μηνυμάτων σε εισαγωγικά και αποθήκευση της τιμής τους
\"[^\"]*\"          { yylval.str = strdup(yytext); return STRING_LITERAL; }

// Operators and Symblols
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"=" { return '='; }
";" { return ';'; }
"," { return ','; }
"(" { return '('; }
")" { return ')'; }

"\\bye"             { line_num++; } // Για να αυξήσουμε τον μετρητή γραμμών
[ \t]+              { /* Αγνοούμε τα κενά και τα tabs */ }
"MINE#".* { /* Αγνοούμε τα σχόλια */ }

//ERROR HANDLER
.   { printf("ΛΑΘΟΣ! ΑΓΝΩΣΤΟΣ ΧΑΡΑΚΤΗΡΑΣ '%s' στην γραμμή %d\n", yytext, line_num); }

%%

int yywrap() {
    return 1;
}
