%{
	#include <stdlib.h>
	#include <string.h>
	#include "bison.tab.h"
	#include "fichier.h"

	int isConstant = -1;
	int isInterger = -1;
	
%}

blanc		   [ \t]+
saut		   [\n]
Idf		       [a-z][_a-z0-9]*[a-z0-9]|[a-z]
Float		   [0-9]+"."[0-9]+
Int	       	   [0-9]+
Comment 	   "/*"(.*|{saut}*)*"*/"|"//".*{saut}
define         "define"
Uint           "Uint"
Ufloat         "Ufloat"
CHECK          "CHECK"
REPEAT         "REPEAT"
ENDCHECK       "ENDCHECK"
ENDREPEAT      "ENDREPEAT"
egal           "=="
dif            "!="
supG           ">="
infG           "<="


%% 
{define}          {afficher_ent("motCle     ");isConstant = 1;return define;} 
{Ufloat}          {afficher_ent("motCle     ");isInterger = 0;return Ufloat;}  
{Uint}            {afficher_ent("motCle     ");isInterger = 1;return Uint;}
{CHECK}           {afficher_ent("motCle     ");return CHECK;}  
{REPEAT}          {afficher_ent("motCle     ");return REPEAT;}
{ENDCHECK}        {afficher_ent("motCle     ");return ENDCHECK;}
{ENDREPEAT}       {afficher_ent("motCle     ");return ENDREPEAT;}
{egal}            {afficher_ent("comparaison");return egal;}
{dif}             {afficher_ent("comparaison");return dif;}
{supG}            {afficher_ent("comparaison");return supG;}
{infG}            {afficher_ent("comparaison");return infG;}
"<"               {afficher_ent("comparaison");return '<';} 
">"               {afficher_ent("comparaison");return '>';}
"&"               {afficher_ent("Ologique   ");return '&';}
"|"               {afficher_ent("Ologique   ");return '|';}
"+"               {afficher_ent("OperArt    ");return '+';}
"-"               {afficher_ent("OperArt    ");return '-';}
"*"               {afficher_ent("OperArt    ");return '*';}
"/"               {afficher_ent("OperArt    ");return '/';}
"="               {afficher_ent("affect     ");return '=';}
","               {afficher_ent("separateur ");return ',';}
";"               {afficher_ent("separateur ");isInterger = 2; isConstant = 2;return ';';} 
"{"               {afficher_ent("acolad     ");return '{';}
"}"               {afficher_ent("acolad     ");return '}';}
"("               {afficher_ent("parnts     ");return '(';}
")"               {afficher_ent("parnts     ");return ')';}
":"               {afficher_ent("separateur ");return ':';}
"!"               {afficher_ent("negation   ");return '!';}
{Comment} 		    {Count_SautLinge(yytext); afficher_ent("commentaire");}
{Idf}		        {if(yyleng <= 8) {afficher_ent("idf        "); traitement(yytext, isConstant, isInterger); isConstant = 0;return idf;} else afficher_erreur("Idf trés long (plus que 8 caractères)");}
{Float} 		    {afficher_ent("Ufloat     "		);return Float;}
{Int} 			    {if(atoi(yytext) <= 32767) {afficher_ent("Uint        ");return Int;}else afficher_erreur("Uint trés long (supérieur à 32767)");  }
{blanc}  		    {colonne += yyleng;}
{saut}   		    {colonne =1; line++; if(un_truc_a_ete_affiche) {if(afficherPartieSyntax) printf("\n"); un_truc_a_ete_affiche = 0;}}
.	 		    {printf("%s",yytext);afficher_erreur("mot non reconnu");}
%%

int yywrap()
	{
		return 1;
	}
