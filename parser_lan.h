%{
#include <stdio.h>
#include <math.h> // Απαραίτητο για τις συναρτήσεις empower και box

void yyerror(const char *s);
int yylex();
extern int line_num;
%}

// Δήλωση των Tokens που επιστρέφει το Flex 
%token PRINT EMPOWER BOX INT_LITERAL IDENTIFIER

// Κανόνες προτεραιότητας των πράξεων 
%left '+' '-'
%left '*' '/' 

%%

program:
    program statement
    | /* κενό */
    ;

statement:
    IDENTIFIER '=' expression ';'           { printf("Εκχώρηση στη μεταβλητή\n"); }
    | PRINT '(' expression ')' ';'          { printf("Εντολή bazinga\n"); }
    | PRINT '(' '"' IDENTIFIER '"' ')' ';'  { printf("Εκτύπωση μηνύματος\n"); }
    ;

expression:
    INT_LITERAL                             { $$ = $1; }
    | IDENTIFIER                            { /* Εδώ θα έπρεπε να πάρεις την τιμή */ }
    | expression '+' expression             { $$ = $1 + $3; }
    | expression '-' expression             { $$ = $1 - $3; }
    | expression '*' expression             { $$ = $1 * $3; }
    | expression '/' expression             { $$ = $1 / $3; }
    | EMPOWER '(' expression ',' expression ')' { $$ = pow($3, $5); }
    | BOX '(' expression ')'                { $$ = $3 * $3; }
    | '(' expression ')'                    { $$ = $2; }
    ;

%%
