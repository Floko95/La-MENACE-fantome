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

void save_graphe(boite* b, boite** adresse, FILE* save)
{
  int32_t n=0;
  if(b!=NULL)
  {
    int32_t i = 0;
    if(checkfree(b, adresse))
    {
      fwrite(&(b->bille), sizeof(int64_t), 1, save);
      while(adresse[n]!=NULL)                                                   //on trouve la premiere place libre dans adresse
        n++;
      adresse[n]=b;
    }

    for(i = 0; i<nb_case_libre(b->terrain); i++)
    {
      save_graphe(b->suivants[i],adresse,save);
    }
  }
}

void charger_graphe(boite* b, boite** adresse, FILE* load)
{
  int32_t n=0;
  if(b!=NULL)
  {
    int32_t i = 0;
    if(checkfree(b, adresse))
    {
      fread(&(b->bille), sizeof(int64_t), 1, load);
      while(adresse[n]!=NULL)                                                   //on trouve la premiere place libre dans adresse
        n++;
      adresse[n]=b;
    }

    for(i = 0; i<nb_case_libre(b->terrain); i++)
    {
      charger_graphe(b->suivants[i],adresse,load);
    }
  }
}

void free_graphe(boite* b, boite** adresse)
{
  if(b!=NULL && checkfree(b,adresse))                                           //On verifie que b ne pointe pas sur NULL et qu'il na pas déjà été libéré
  {
    uint32_t i = 0, caseLibre = nb_case_libre(b->terrain), n=0;                 //declaration des variable
    boite* adr[SIZE] = {NULL};                                                  //adr est une copie de b->suivants.
    for(i=0; i<caseLibre; i++)                                                  //on effectue la copie
    {
      adr[i]=b->suivants[i];
    }
    while(adresse[n]!=NULL)                                                     //on trouve la premiere place libre dans adresse
      n++;
    adresse[n]=b;                                                               //on stocke b dans addresse
    if(b->suivants!=NULL)
      myfree(b->suivants);
    myfree(b);                                                                  //on libere b
    for(i=0; i<caseLibre; i++)
    {
      free_graphe(adr[i],adresse);                                              //on poursuit sur les fils
    }
  }
}

int checkfree(boite* b, boite** adresse)
{
  uint32_t i = 0;
  for(i=0; i<mytabsize(adresse, sizeof(boite*)); i++)
  {
    if(adresse[i]==b) return 0;
  }
  return 1;
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

uint64_t get_bille(uint64_t billes, int Case)
{
  return (billes&CreerMasque(Case,MASQUE_BILLE))/(CreerMasque(Case,MASQUE_BILLE)/127);
}
uint64_t set_bille(uint64_t billes, int Case, int value) //renvoie l'entier billes avec la bille souhaitée modifiée
{
    return billes|(value<<((Case-1)*7));
}
uint64_t sommeBilles(uint64_t billes)
{
	uint32_t i;
	uint32_t somme=get_bille(billes,1);
	for (i=1;i<9;i++)
	{
		somme+= get_bille(billes,i+1);
	}
	return somme;
}
int ProchainCoup(uint64_t billes)	//renvoie la case (1 à 9) où l'IA devra jouer le prochain coup
{
	uint32_t nombre_aleatoire = rand()%sommeBilles(billes);

	printf("nb alea: %d\n", nombre_aleatoire);

	uint32_t sommetmp=0;
	int i;
	for(i=0;i<9;i++)
	{
		if ((nombre_aleatoire >= sommetmp) & (nombre_aleatoire < sommetmp + get_bille(billes,i+1)))
			return i+1;
		else
			sommetmp+=get_bille(billes,i+1);
	}
	return 0;
}
 int partieFinie(uint32_t terrain)
{
    //horizontal
    if(terrain & 0x3F == 0x15) return ROND;
    if(terrain & 0x3F == 0x2A) return CROIX;

    if(terrain & 0xFC0 == 0x540) return ROND;
    if(terrain & 0xFC0 == 0xA80) return CROIX;

    if(terrain & 0x3F000 == 0x15000) return ROND;
    if(terrain & 0x3F000 == 0x2A000) return CROIX;
    //vertical
    if(terrain & 0x30C3 == 0x1041) return ROND;
    if(terrain & 0x30C3 == 0x2082) return CROIX;

    if(terrain & 0xC30C == 0x4104) return ROND;
    if(terrain & 0xC30C == 0x8208) return CROIX;

    if(terrain & 0x30C30 == 0x10410) return ROND;
    if(terrain & 0x30C30 == 0x20820) return CROIX;
    //diagonal
    if(terrain & 0x30303 == 0x10101) return ROND;
    if(terrain & 0x30303 == 0x20202) return CROIX;

    if(terrain & 0x3330 == 0x1110) return ROND;
    if(terrain & 0x3330 == 0x2220) return CROIX;

    return 0;//personne ne gagne


}
//-----------------------interface utilisateur-----------------------------
int promptCoup()
{
    printf("entrez un entier entre 1 et 9 pour déterminer la case où jouer\n (1 pour en haut à gauche et 9 pour en bas à droite)\n");
    int i;
    scanf("%d",&i);
    while(i<=0 | i>9)
    {
        printf("N'entrez qu'un entier de 1 à 9");
      scanf("%d",&i);
    }
    return i;

}

int32_t promptGamemode()
{

    int32_t i=-1;
     while(i<0)
        {
            printf("Voulez vous jouer contre l'IA ou voulez vous que l'IA joue contre elle-même? \n(0 pour JvsIA et N (positif) pour N parties de IAvsIA)");
            scanf("%d,&i");
        }
    return i;
}

boite* choix_graphe()
{
    boite * graphe = charger_graphe();
    if(graphe!=NULL)
    {
        int i=-1;
        while(i!= 1 & i !=0)
        {
            printf("Fichier d'IA trouvé.Voulez vous jouer avec cet IA ou en créer une nouvelle?\n(0 pour jouer,1 pour créer)");
            scanf("%d",&i);
        }
        if(i==0)
        {
            return graphe;
        }
        else
        {
            printf("Création d'une nouvelle IA.");
        }
    }
    else
    {
         printf("Aucun fichier valable de IA n'a été trouvé. Création d'un nouveau potentiel terminator.");
    }
    int32_t* tab = mymalloc(sizeof(int32_t)*850);
    boite** add = mymalloc(sizeof(boite*)*850);
    boite* b = creer_noeud(0);
    creer_graphe(b,tab,add);
    return b;


}
//----------------------------------------------------------------------
int main(int argc, char const *argv[])
{
     srand(time(NULL));
  int32_t* tab = mymalloc(sizeof(int32_t)*10000);
  boite** add = mymalloc(sizeof(boite*)*10000);
  boite* b = creer_noeud(0);
  //fprintf(stdout, "%p\n", b);
  creer_graphe(b,tab,add);
  //int32_t a =0x2AAAA, b=0x2AAAA;
  //printf("%d | %d | %d ",rotation180(a, b),get_case(a, 9),get_case(b, 1));
  //---tests des billes----------------
    /*uint64_t c = 0x7FFFFFFFFFFFFFFF ;
	printf("%ld\n",c);
	printf("%ld\n",get_bille(c,1) );
	printf("%ld\n",get_bille(c,5) );
	printf("%ld\n",get_bille(c,9) );
	printf("%ld\n",sommeBilles(c) );
	printf("%ld\n",ProchainCoup(c) );
	printf("%ld\n",ProchainCoup(c) ); -1 croix 1 rond */
  return 0;
}
