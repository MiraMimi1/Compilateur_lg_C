%{

#include <stdio.h>
#include <stdlib.h>

	extern FILE *yyin;
	extern int line,colonne;
	extern char* yytext;
 	
	

%}

%token idf Int Float  Uint define  egal dif supG infG Ufloat CHECK ENDCHECK REPEAT ENDREPEAT   
%token '{' '}' '=' ';' ',' ':' '>' '<' '(' ')' '*' '+' '-' '/' '!'

%%

PROG            : Entree  						{printf("\ncorrect syntaxiquement\n"); afficherLaTable();};
Entree          : idf '{' CodeInterieur '}';
CodeInterieur	:  D  '{' CodeInterieur2 ;
CodeInterieur2  :  I '}'  ;			// ca a l'air bizzare ... mais c'est pour la factorisation
//-Declarations----------------------------------------

D 				: Var | Const ;
Var				: type listVariables ;
type			: Ufloat | Uint ;
listVariables	: idf VarEND ;
VarEND			:  ';' D | ';' | ',' listVariables ;

Const			: define CstType ;
CstType			: CstUfloat | CstUint ;
CstUint			: Uint idf '=' Int ConstEND ;
CstUfloat		: Ufloat idf '=' Float ConstEND ;
ConstEND		:  ';' D | ';';

//-Instructions----------------------------------------
I 				: Instruction I | Instruction ;
Instruction 	: affect_inst | CHECK_inst | REPEAT_inst ;
affect_inst 	: affectation ';' ;
affectation     : idf '=' Exp ;
// !!!!! L'ordre est important !!! pour gerer les prioritées : le ou |, le et &,  la negation '!', < > == != <= >=, + - ,  * / --- le dernier est le plus prioritére
//-CONDITIONS------------------------------------------

condition	    : condition2 '|' condition | condition2 ; // la condition peut etre apllée aussi 'exp logique'
condition2	    : condition3 '&' condition2 | condition3 ;
condition3		: '!'condition3  | conditionEND ;
conditionEND	: conditionParts | Exp OprCmpare Exp ; //####
conditionParts  : '('condition')';
OprCmpare		: egal | dif | '<' | infG | '>' | supG ;
//-Expressions arithmétiques---------------------------

Exp 			: Exp2 PlusMoins Exp | Exp2  ;
PlusMoins		: '+' | '-' ;
Exp2 			: Exp3 MultDiv Exp2 | Exp3 ;
MultDiv			: '*' | '/' ;
Exp3			: '('Exp')'| idf | Int | Float ; //####
//-CHECK et REPEAT-------------------------------------

CHECK_inst		: CHECK '('condition')'':' I ':' I ENDCHECK  ;
REPEAT_inst		: REPEAT ':' affectation ':''(' condition ')'':' affectation ':' I ENDREPEAT ;

%%
int yyerror(char *msg)
{
	printf(" %s   ligne  %d , colonne  %d , entitee:   %s \n", msg,line,colonne,yytext);
	return 0;
}

int main()
{
	yyin=fopen("input.txt","r");
	yyparse();
	return 0;
	
	//{printf("correct syntaxiquement\n");afficherLaTable();};
}
