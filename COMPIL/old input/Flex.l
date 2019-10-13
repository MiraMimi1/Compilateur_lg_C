%{
	#include "bison.tab.h"
	#include "fichier.h"
	
%}

idf	   [a-z]+
entier [0-9]+
bl [ \t]
	
%%
	
{idf}	 { traitement( init_entite(yytext, "idf", "idf"))		; return idf;	 }
{entier} { traitement( init_entite(yytext, "entier", "entier"))	; return entier; }
{bl} 	 {	}
.		 {printf("%s : erreur",	yytext);}

%%
	
	int yywrap()
	{
		return 1; // 
	}

// flex 	Flex.l
// bison	-d bison.y
// gcc bison.tab.c lex.yy.c -o prog
// 

// flex Flex.l; bison -d bison.y ;gcc bison.tab.c lex.yy.c -o prog

