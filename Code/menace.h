#ifndef MEN_H
#define MEN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define SIZE 9

#define CROIX 2
#define ROND  1
#define VIDE  0

#define MASQUE_CASE 0
#define MASQUE_BILLE 1

typedef struct _boite
{
  int terrain;
  uint64_t bille
  struct _boite **suivants;
} boite;



#endif
