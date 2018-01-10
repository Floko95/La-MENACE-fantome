#ifndef MEN_H
#define MEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//Definition des constante symbolique.
#define SIZE 9

#define CROIX 2
#define ROND  1
#define VIDE  0

#define MASQUE_CASE 0
#define MASQUE_BILLE 1


typedef struct _boite
{
  int32_t terrain;
  int64_t bille;
  struct _boite **suivants;
} boite;

int set_case(int terrain, int cases, int value);
int get_case(int terrain, int cases);
int nb_case_libre(int terrain);
int symetrie_v(int32_t t1, int32_t t2);
int symetrie_h(int32_t t1, int32_t t2);
int symetrie_d1(int32_t t1, int32_t t2);
int symetrie_d2(int32_t t1, int32_t t2);
int rotationD90(int32_t t1,int32_t t2);
int rotationG90(int32_t t1,int32_t t2);
int64_t CreerMasque(int Case, int typeMasque);
void creer_graphe(boite* b, int32_t* figure, boite** addresse);
int32_t verify_tab(int32_t terrain, int32_t* tab);
boite* creer_noeud(int32_t terrain);


#endif
