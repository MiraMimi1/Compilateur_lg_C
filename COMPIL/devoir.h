#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct entite_type
{
	char * entite;
	char * type;
	char * nature;

}entite_type;

typedef struct List
{
entite_type x;
struct List *svt;
}List;

//la fonction ajouter prende en parametre l'adresse du pointeur de la liste  , la position ou on veut ajouter l'element et l'elemnet a ajouter
void ajouter(List **Liste,entite_type Entree){

       List *temp=malloc(sizeof(*temp));
       temp->x=Entree;
       temp->svt=(*Liste);
       (*Liste)=temp;

			 List *temp1 =(*Liste);




}
bool existElemet(List *L,entite_type Entree){

    while(L!=NULL){
    if(!strcmp(L->x.entite,Entree.entite))
    return true;
    L=L->svt;
    }
    return false;

}

entite_type init_entite(char * entite, char * type, char * nature)
{
  entite_type e ;
	e.entite = strdup(entite);
  e.type   = strdup(type);
  e.nature = strdup(nature);
  return e;
}
