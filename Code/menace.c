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

uint64_t CreerMasque(int Case, int typeMasque)		//case de 1 à 9 et non de 0 à 8
{
	assert(Case!=0);
	if(typeMasque==MASQUE_CASE)
        return 3 <<(Case-1) *2;
	else if(typeMasque==MASQUE_BILLE)
        return 127 <<(Case-1) *7;
    else
        return 0;
}
int main(int argc, char const *argv[]) {

	printf("%d\n",CreerMasque(1,MASQUE_BILLE));
	printf("%d\n",CreerMasque(9,MASQUE_BILLE));
	printf("%d\n",CreerMasque(3,MASQUE_CASE));
	printf("%d\n",CreerMasque(9,MASQUE_CASE));
  return 0;
}
