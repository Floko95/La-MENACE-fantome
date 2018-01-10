#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "menace.h"
#include "mytab.h"


int set_case(int terrain, int cases, int value) // cases diot etre le numéro de la case; value doit etre CROIX ROND ou VIDE
{
    return terrain|(value<<((cases-1)*2));
}

int get_case(int terrain, int cases)// cases diot etre une des constant le numéro de la case;
{
  return (terrain&CreerMasque(cases,MASQUE_CASE))/(cases/3);
}

int nb_case_libre(int terrain)
{
  int cpt = 0, i;
  for(i=0; i<SIZE; i++)
  {
    cpt = cpt + ((terrain&(3<<i)) == 0);
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
	return (get_case(t1,1)==get_case(t2,3)) && (get_case(t1,2)==get_case(t2,6)) && (get_case(t1,3)==get_case(t2,9)) && (get_case(t1,4) == get_case(t2,2)) && (get_case(t1,6) == get_case(t2,8)) && (get_case(t1,7)== get_case(t2,1)) && (get_case(t1,8)==get_case(t2,4)) && (get_case(t1,9) == get_case(t2,7)) ;
}

int rotationG90(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 90 degrés vers la gauche on obtient t2
{
	return (get_case(t1,1)==get_case(t2,7)) && (get_case(t1,2)==get_case(t2,4)) && (get_case(t1,3)==get_case(t2,1)) && (get_case(t1,4) == get_case(t2,8)) && (get_case(t1,6) == get_case(t2,2)) && (get_case(t1,7)== get_case(t2,9)) && (get_case(t1,8)==get_case(t2,6)) && (get_case(t1,9) == get_case(t2,3)) ;
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
  if(nb_case_libre(b->terrain)!=0)
  {
    int32_t i=0, j=0, n=0, caseLibre = nb_case_libre(b->terrain);

    b->suivants = mymalloc(sizeof(boite*)*caseLibre);
    for(i=0; i<SIZE;i++)
  	{
  		if(get_case(b->terrain,i+1)==0)
  		{
  			if((j=verify_tab(b->terrain,figure))>0)
        {
          if(caseLibre%2 == 1)
          {
            b->suivants[n]=creer_noeud(set_case(b->terrain, i+1, ROND));
            figure[-j] = set_case(b->terrain, i+1, ROND);
            addresse[-j] = b->suivants[n];
          }
          else
          {
            b->suivants[n]=creer_noeud(set_case(b->terrain, i+1, CROIX));
            figure[-j] = set_case(b->terrain, i+1, CROIX);
            addresse[-j] = b->suivants[n];
          }
        }
        else
        {
          b->suivants[n] = addresse[j];
        }
        creer_graphe(b->suivants[n], figure, addresse);
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
        || symetrie_d2(terrain, tab[i]) || rotationD90(terrain, tab[i]) || rotationG90(terrain, tab[i])) return i;
	}
	return -i;
}


boite* creer_noeud(int32_t terrain)
{
	boite* b= malloc(sizeof(boite));
	b->terrain = terrain;
	b->bille = (1<<63)-1;
	b->suivants = NULL;
	return b;

}

int main(int argc, char const *argv[]) {
  uint64_t i = 1<<60;
	printf("%d\n",CreerMasque(1,MASQUE_BILLE));
	printf("%d\n",CreerMasque(9,MASQUE_BILLE));
	printf("%d\n",CreerMasque(3,MASQUE_CASE));
	printf("%d\n",CreerMasque(9,MASQUE_CASE));
  fprintf(stdout,"%d\n",i);
  return 0;
}
