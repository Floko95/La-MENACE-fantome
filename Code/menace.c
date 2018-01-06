#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "menace.h"



int set_case(int terrain, int cases, int value) // cases diot etre le numéro de la case; value doit etre CROIX ROND ou VIDE
{
    return terrain|(value<<((cases-1)*2));
}

int get_case(int terrain, int cases)// cases diot etre une des constant le numéro de la case;
{
  return (terrain&(3<<((cases-1)*2)))/(cases/3);
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

int CreerMasque(int Case, int typeMasque)		//case de 1 à 9 et non de 0 à 8
{
	assert(Case!=0);
	uint64_t masque=0;
	uint32_t limite;
	uint32_t i;
	uint32_t stockage_info=0;
	if(typeMasque==MASQUE_CASE)
	{
		limite=18;						//un terrain est codé sur 18 bits
		stockage_info=2;				//une case sur 2 bits
	}
	else if(typeMasque==MASQUE_BILLE)
	{
		limite=64;						//les billes totales sur 64 bits
		stockage_info=7;				//les billes d'une case sur 7 bits
	}

	for(i=0;i<limite;i++)						//création bit par bit du masque
	{
		if(i< Case * stockage_info & i>= (Case-1) * stockage_info)		//si le bit parcouru est  un bit de la case souhaitée
			masque+= pow(2,i);					//on met le bit à 1 ( donc on ajoute 2^i)
												//sinon il sera à 0 et on passe au bit suivant
	}
	return masque;
}
int main(int argc, char const *argv[]) {

	printf("%d\n",CreerMasque(1,MASQUE_BILLE));
	printf("%d\n",CreerMasque(9,MASQUE_BILLE));
	printf("%d\n",CreerMasque(3,MASQUE_CASE));
	printf("%d\n",CreerMasque(9,MASQUE_CASE));
  return 0;
}
