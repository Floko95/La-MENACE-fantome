#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "menace.h"
#include "mytab.h"


int set_case(int terrain, int cases, int value) // cases diot etre le numéro de la case; value doit etre CROIX ROND ou VIDE
{
    return terrain|(value<<((cases-1)*2));
}

int32_t get_case(int32_t terrain, int32_t cases)// cases diot etre une des constant le numéro de la case;
{
  return (terrain&CreerMasque(cases,MASQUE_CASE))/(CreerMasque(cases,MASQUE_CASE)/3);
}

int nb_case_libre(int terrain)
{
  int cpt = 0, i;
  for(i=0; i<SIZE; i++)
  {
    cpt = cpt + (get_case(terrain, i+1) == VIDE);
  }

  return cpt;
}

int symetrie_v(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie verticale de t2
{
	return 	(get_case(t1,1)==get_case(t2,3))&&(get_case(t1,2)==get_case(t2,2))&&(get_case(t1,3)==get_case(t2,1))&&
		(get_case(t1,4)==get_case(t2,6))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,4))&&
		(get_case(t1,7)==get_case(t2,9))&&(get_case(t1,8)==get_case(t2,8))&&(get_case(t1,9)==get_case(t2,7));
}


int symetrie_h(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie horizontale de t2
{
	return 	(get_case(t1,1)==get_case(t2,7))&&(get_case(t1,4)==get_case(t2,4))&&(get_case(t1,7)==get_case(t2,1))&&
		(get_case(t1,2)==get_case(t2,8))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,8)==get_case(t2,2))&&
		(get_case(t1,3)==get_case(t2,9))&&(get_case(t1,6)==get_case(t2,6))&&(get_case(t1,9)==get_case(t2,3));
}


int symetrie_d1(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie diagonale(/) de t2
{
	return 	(get_case(t1,1)==get_case(t2,9))&&(get_case(t1,2)==get_case(t2,6))&&(get_case(t1,3)==get_case(t2,3))&&
		(get_case(t1,4)==get_case(t2,8))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,2))&&
		(get_case(t1,7)==get_case(t2,7))&&(get_case(t1,8)==get_case(t2,4))&&(get_case(t1,9)==get_case(t2,1));
}


int symetrie_d2(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie diagonale(\) de t2
{
	return 	(get_case(t1,1)==get_case(t2,1))&&(get_case(t1,2)==get_case(t2,4))&&(get_case(t1,3)==get_case(t2,7))&&
		(get_case(t1,4)==get_case(t2,2))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,8))&&
		(get_case(t1,7)==get_case(t2,3))&&(get_case(t1,8)==get_case(t2,6))&&(get_case(t1,9)==get_case(t2,9));
}

int rotationD90(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 90 degrés vers la droite on obtient t2
{
	return (get_case(t1,1)==get_case(t2,3)) && (get_case(t1,2)==get_case(t2,6)) && (get_case(t1,3)==get_case(t2,9))
  && (get_case(t1,4) == get_case(t2,2)) && (get_case(t1,5)== get_case(t2,5)) && (get_case(t1,6) == get_case(t2,8)) && (get_case(t1,7)== get_case(t2,1))
  && (get_case(t1,8)==get_case(t2,4)) && (get_case(t1,9) == get_case(t2,7)) ;
}
int rotation180(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 90 degrés vers la droite on obtient t2
{
	return (get_case(t1,1)==get_case(t2,9)) && (get_case(t1,2)==get_case(t2,8)) && (get_case(t1,3)==get_case(t2,7))
  && (get_case(t1,4) == get_case(t2,6)) &&(get_case(t1,5)== get_case(t2,5))&& (get_case(t1,6) == get_case(t2,4)) && (get_case(t1,7)== get_case(t2,3))
  && (get_case(t1,8)==get_case(t2,2)) && (get_case(t1,9) == get_case(t2,1)) ;
}

int rotationG90(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 180 degrés vers la gauche on obtient t2
{
	return (get_case(t1,1)==get_case(t2,7)) && (get_case(t1,2)==get_case(t2,4)) && (get_case(t1,3)==get_case(t2,1))
  && (get_case(t1,4) == get_case(t2,8)) &&(get_case(t1,5)== get_case(t2,5))&& (get_case(t1,6) == get_case(t2,2)) && (get_case(t1,7)== get_case(t2,9))
  && (get_case(t1,8)==get_case(t2,6)) && (get_case(t1,9) == get_case(t2,3)) ;
}

int64_t CreerMasque(int Case, int typeMasque)		//case de 1 à 9 et non de 0 à 8
{
	assert(Case!=0);
	if(typeMasque==MASQUE_CASE)
        return 3 <<(Case-1) *2;
	else if(typeMasque==MASQUE_BILLE)
        return 127 <<(Case-1) *7;
    else
        return 0;
}

void creer_graphe(boite* b, int32_t* figure, boite** addresse)
{
  if(b!=NULL && nb_case_libre(b->terrain)!=0)
  {
    int32_t i=0, j=0, n=0, caseLibre = nb_case_libre(b->terrain), symbole = VIDE;
    boite* tmp = NULL;
    b->suivants = mymalloc(sizeof(boite*)*caseLibre);
    for(i=0; i<SIZE;i++)
  	{
  		if(get_case(b->terrain,i+1)==VIDE)
  		{

        if(caseLibre%2 == 1)
        {
          symbole = ROND;
        }
        else
        {
          symbole = CROIX;
        }

        tmp = creer_noeud(set_case(b->terrain, i+1, symbole));
        if((j=verify_tab(tmp->terrain,figure))<=0)
        {
          b->suivants[n] = tmp;
          figure[-j] = tmp->terrain;
          addresse[-j] = b->suivants[n];
          afficheTerrain(tmp->terrain);
          creer_graphe(b->suivants[n], figure, addresse);
        }
        else
        {
          b->suivants[n] = addresse[j];
        }

        n++;

  		}
  	}
  }
}

int32_t verify_tab(int32_t terrain, int32_t* tab)
{
	int32_t i = 0;
	for(i=0; tab[i]!=0; i++)
	{
		if (symetrie_v(terrain, tab[i]) || symetrie_h(terrain, tab[i]) || symetrie_d1(terrain, tab[i])
        || symetrie_d2(terrain, tab[i]) || rotation180(terrain,tab[i]) || rotationD90(terrain, tab[i])
        || rotationG90(terrain, tab[i]) || terrain == tab[i]) return i;
	}
	return -i;
}


boite* creer_noeud(int32_t terrain)
{
	boite* b= mymalloc(sizeof(boite));
	b->terrain = terrain;
	b->bille = 1;
  b->bille = (b->bille<<63);
  (b->bille)--;
	b->suivants = NULL;
	return b;

}
void afficheTerrain(uint32_t terrain)
{
  for(int i=0;i<SIZE/3;i++)
  {
    for (int j=0;j<SIZE/3;j++)
    {
      printf("%d|",get_case(terrain,i*(SIZE/3)+1+j));
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char const *argv[])
{
  int32_t* tab = mymalloc(sizeof(int32_t)*10000);
  boite** add = mymalloc(sizeof(boite*)*10000);
  boite* b = creer_noeud(0);
  //fprintf(stdout, "%p\n", b);
  creer_graphe(b,tab,add);
  //int32_t a =0x2AAAA, b=0x2AAAA;
  //printf("%d | %d | %d ",rotation180(a, b),get_case(a, 9),get_case(b, 1));
  return 0;
}
