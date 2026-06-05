%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Απαραίτητο για τις συναρτήσεις empower και box

void yyerror(const char *s);
int yylex();
extern int line_num;

//Ορίζω δομή πίνακα συμβόλων ώστε να διατηρούνται οι τιμές των μεταβλητών
#define MAX_VARIABLES 50

typedef struct{
    char *name;
    int value;
}VARIABLE;

VARIABLE symbol_table[MAX_VARIABLES];
//Αρχικοποιώ count για το σύνολο των μεταβλητών που βρίσκονται στον πίνακα
int count=0;

//Ορίζω συνάρτηση γαι εύρεση και προσθήκη μετάβλητης και εκχώρησης τιμής
void set_val(char *name,int value){
    for(int i=0;i<count;i++){
        if(strcmp(symbol_table[i].name,name)==0){
            //Ενημέρωση τιμής αν υπάρχει ήδη
            symbol_table[i].value=value;
            return;   
        }
    }
    //Προσθήκη στον πίνακα συμβόλων αν δεν υπάρχει η συγκεκριμένη μεταβλητή
    if(count<MAX_VARIABLES){
        symbol_table[count].name=strdup(name);
        symbol_table[count].value=value;
        count++;
    }else{
        //Περίπτωση που γέμισε ο πίνακας συμβόλων
        printf("Ο Πίνακας συμβόλων έχει γεμίσει!");
    }
}

//Ορίζω συνάρτηση για ανάκτηση τιμής μιας μεταβλητής
int get_val(char *name){
    for(int i=0;i<count;i++){
        if(strcmp(symbol_table[i].name,name)==0){
            return symbol_table[i].value;
        }
    }
    printf("Προσοχή: Η μεταβλητή %s στην γραμμή %d δεν έχει αρχικοποιηθεί\n",name, line_num);
    //Επιστρέφει 0 στην περίπτωση που δεν βρεθεί τιμή σε μεταβλητή
    return 0;
}
%}

//Ορισμός union για τους τύπους δεδομένων
%union{
    int number;
    char *str;
}

// Δήλωση των Tokens που επιστρέφει το Flex και οι τιμές τους
%token PRINT EMPOWER BOX 
%token <number> INT_LITERAL
%token <str> IDENTIFIER STRING_LITERAL

//Δήλωση τύπου για κανόνα expression
%type <number> expression

// Κανόνες προτεραιότητας των πράξεων 
%left '+' '-'
%left '*' '/' 

%%

program:
    program statement
    | /* κενό */
    ;

statement:
    IDENTIFIER '=' expression ';'{
        //Αποθήκευση μεταβλητής και τιμής στον πίνακα συμβόλων 
        set_val($1,$3);
        printf("Εκχώρηση %s=%d\n",$1,$3);
        //Αποδέσμευση μνήμης string
        free($1);
    }
    | PRINT '(' expression ')' ';'      {printf("bazinga %d\n",$3);}
    | PRINT '(' STRING_LITERAL ')' ';'   {printf("bazinga %s\n",$3);
        //Αποδέσμευσυ μνήμης string
        free($3);    
    }
    ;
expression:
    INT_LITERAL                             { $$ = $1; }
    | IDENTIFIER                            { $$ = get_val($1); free($1); } //Διαβάσμα τιμής από τον πίνακα συμβόλων
    | expression '+' expression             { $$ = $1 + $3; }
    | expression '-' expression             { $$ = $1 - $3; }
    | expression '*' expression             { $$ = $1 * $3; }
    | expression '/' expression             { 
        //Περίπτωση διαίρεσης με το 0
        if($3==0){
            yyerror("Σφάλμα διαίρεσης με το 0!");
            //Θέτω το αποτέλεσμα ίσο με 0 για να αποφύγω το κρασάρισμα
            $$=0;
        }else{
            $$=$1/$3;
        }
    }
    | EMPOWER '(' expression ',' expression ')' { $$ = pow($3, $5); }
    | BOX '(' expression ')'                { $$ = $3 * $3; }
    | '(' expression ')'                    { $$ = $2; }
    ;

%%
void yyerror(const char *s){
    fprintf(stderr, "Συντακτικό Λάθος: γραμμή %d, %s\n",line_num,s);
}
int main(int argc, char **argv){
    //Εκίνηση compiling 
    yyparse();
    return 0;
}
