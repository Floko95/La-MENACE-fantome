#ifndef MEN_H
#define MEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "mytab.h"

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
uint64_t get_bille(uint64_t billes, int Case);
uint64_t set_bille(uint64_t billes, int Case, int value);
uint64_t sommeBilles(uint64_t billes);
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
int32_t verify_sym(int32_t terrain, int32_t t2);
boite* creer_noeud(int32_t terrain);
void afficheTerrain(uint32_t terrain);
void charger_graphe(boite* b, boite** adresse, FILE* file);
void save_graphe(boite* b, boite** adresse, FILE* file);
void free_graphe(boite* b, boite** adresse);
int checkfree(boite* b, boite** adresse);
int ProchainCoup(uint64_t billes);
int partieFinie(uint32_t terrain);
void set_passage(boite * b);
int est_passe(boite* b);
void modifier_billes(boite* b, int8_t gagnant);
//---Interface utilisateur
int promptCoup();
int32_t promptGamemode();
boite* choix_graphe();
int32_t changerSymbole(int32_t symbole);
int promptPremierJoueur();




#endif
