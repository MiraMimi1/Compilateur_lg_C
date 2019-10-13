#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "devoir.h"

//=========================================================================================================================
	int line=1, colonne=1;
	int un_truc_a_ete_affiche = 0; // utiliser pour séparer l'affichage de differetes lignes ...
	int afficherPartieSyntax = 0;
//-------------------------------------------------------------------------------------------------------------------------
	void afficher_ent(char* type_ent) // affiche l'entité et sa catégorie
	{ if(afficherPartieSyntax)
		printf("line %d:\t%s\t%s \n", line ,type_ent, yytext); colonne += yyleng; un_truc_a_ete_affiche = 1;
	}
//-------------------------------------------------------------------------------------------------------------------------
	void Count_SautLinge(char* text) // compter les sauts de lignes dans les commentaires
	{int i;	
		for( i=0; i < strlen(text); i++)
		{
			colonne++; // il faut incrementer la colonne
			if( text[i] == '\n' )
			{
				line++;
				colonne = 1; // remettre la colonne a 1
				if(un_truc_a_ete_affiche && afficherPartieSyntax) {printf("\n"); un_truc_a_ete_affiche = 0;}
			}
		}
			
	}
//-------------------------------------------------------------------------------------------------------------------------
	void afficher_erreur(char* description) // afficher l'erreur et met-a-jour la var colonne
	{
		
			printf("\nerror in line %d colomn %d:\t%s\n>>> %s\n\n", line, colonne, yytext, description); colonne += yyleng;
		un_truc_a_ete_affiche = 1;
	}
//========================================================================================================================= 


int table_deja_affichee = 0;

 int tableDessine=0;
	List *table_symboles = NULL;
	entite_type ent;
	FILE *F=NULL;

char* taillCollone(char * mot){
//fonction qui ajout des espace  à la fin pour  que le mot prend la taill de la collon dans le ficher
  for (size_t i = strlen(mot); i <11; i++) {
    strcat(mot," ");
  }
//  printf("%s|\n",ch );
  return mot;
}
void dessinerUneNouvelleTable(){
    //fonction qui permet de dissiner la premier ligne de la table des symbole  apartir d'un ficher dans le ficher final
    char c;
    FILE *DessinDeLATable=NULL,*Table=NULL;

      DessinDeLATable=fopen("Table/tableDessin.txt","r");
      Table=fopen("Table/table.txt","w");

      c=(char)fgetc(DessinDeLATable);
      while ((c!=EOF)) {
        fputc(c,Table);
        c=(char)fgetc(DessinDeLATable);
      }

      fclose(DessinDeLATable);
      fclose(Table);

}
void ajouterAuFicher(char *entitee,char *type,char *nature){
  FILE *Table=NULL;
  char chaine[strlen(entitee)];
  char  chaine1[strlen(type)];
  char  chaine2[strlen(nature)];
    //copier les chaine données dans des variable local
    strcpy(chaine,entitee);
    strcpy(chaine1,type);
    strcpy(chaine2,nature);

    Table=fopen("Table/table.txt","a");//overture on mode ajouter a la fin
    fprintf(Table," %s |%s|%s|\n",taillCollone(chaine),taillCollone(chaine1),taillCollone(chaine2));
    fclose(Table);
}


void reglerAffichageFicher()
{
	FILE *Table     = NULL;
	FILE *Table_tmp = NULL;
	int positionMax[3] = {0,0,0}; // utilisée pour avoir les tailles max des 3 colonnes



	char text[1000];
	int i, pos = 0, pos_source = 0;

// detection des positionMax
	Table=fopen("Table/table.txt","r");
	fgets(text, 1000, Table);
    while(!feof(Table))
    {
    	pos = 0; // initiallement
    	if (text[0] != '-') // si c'est une ligne, et pas un "__________________" trait
	        for(i=0;i<3; i++)
	        {
	        	while (text[pos] != '|')
	        		pos++;
	        	if (positionMax[i] < pos) //int positionMax[3] : utilisée pour avoir les tailles max des 3 colonnes (jusqu'au '|' inclus)
	        		positionMax[i] = pos;
	        	pos++; // pour sauter la barre '|'
	        }
	    fgets(text, 1000, Table);
    }
	fclose(Table);



char c;
// reecrir le fichier correctement
	Table=fopen("Table/table.txt","r");
	Table_tmp=fopen("Table/Table_tmp.txt","w");

	fgets(text, 1000, Table);
	while(!feof(Table))
    {
    	pos_source = 0;
    	pos = 0; // initiallement
    	if (text[0] == '-') // si c'est une ligne, et pas un "--------------------" trait
    	{
    		for(i=0;i<3; i++)
	        {
	        	while (pos < positionMax[i])
	        	{
	        		fputc('-', Table_tmp);
	        		pos++;
	        	}
	        	fputc('+', Table_tmp); /// print "+-------+----------+------------+"
	        	pos++;
	        }

    	}
    	else
	    {
			for(i=0;i<3; i++)
	        {


	        	while(text[pos_source] != '|')
	        	{
	        		fputc(text[pos_source], Table_tmp);
	        		pos_source++;
	        		pos++;
	        	}
	        	pos_source++; // sauter la barre '|'
	        	// completer par des blancs....
	        	while(pos < positionMax[i])
	        	{
	        		fputc(' ', Table_tmp);
	        		pos++;
	        	}
	        	fputc('|', Table_tmp);  /// print "bladqjdqqsjkd    |  idf    |  idf  |"
	        	pos++;
	        }
	    }
	    fputc('\n', Table_tmp); // saut de ligne
	    fgets(text, 1000, Table);
    }
	fclose(Table);
	fclose(Table_tmp);

	remove("Table/table.txt");
	rename("Table/Table_tmp.txt", "Table/table.txt");
}


void traitement(char * entite_txt, int isConstant, int isInteger)
{
	entite_type ent;
	ent.entite = strdup(yytext);



	// le type   : Uint ou Ufloat
	if(isInteger == 0)
		ent.type     = strdup("Ufloat");
	else if ( isInteger == 1)
		ent.type     = strdup("Uint");
	else if ( isInteger == -1)
		ent.type     = strdup("programme");

	// la nature : constante ou variable
	if(isConstant == 0 || (isConstant == 2 && isInteger != 2))
		ent.nature   = strdup("Variable");
	else if ( isConstant == 1)
		ent.nature   = strdup("Constante");
	else if ( isConstant == -1)
		ent.nature   = strdup("programme");

	// les variables non declarée serons de type et de nature inconnue
	if(isInteger == 2)
	{
		ent.type     = strdup("inconnu");
		ent.nature   = strdup("inconnue");
	}


	if(! existElemet(table_symboles, ent))
		  {
				ajouter(&table_symboles,ent);
				 if(!tableDessine){dessinerUneNouvelleTable(); tableDessine=1; }
				 ajouterAuFicher(ent.entite,ent.type,ent.nature);
		  }
}
void  afficherLaTable(){


	if(table_deja_affichee) return;

    FILE *Table=NULL;
    char c;
    reglerAffichageFicher();
      Table=fopen("Table/table.txt","r");
      while ((fscanf(Table,"%c",&c)!=EOF)) {
        printf("%c",c);
      }
      fclose(Table);

     table_deja_affichee = 1;
}
