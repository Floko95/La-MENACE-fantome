
//....
int main(int argc, char const *argv[])
{


choix_graphe();
int32_t choixjoueur = promptGamemode();
uint8_t symbole_courant,tour,i;
uint32_t compteur,test;
int32_t terrain_suivant;
boite * boite_courant;
//b contient la première boite de l'arbre

while(choixjoueur != -1)
{
    boite_courant=b;
    if(choixjoueur==0)
    {
        //debut d'une partie
        if(promptPremierJoueur()==0)
            {
                tour=1;
                test=0;

            }
        else
            {
                tour=-1;
                test=1;
            }
        symbole_courant=ROND;
        while(partieFinie(boite_courant->terrain)==0)
        {
            if(tour==1)
            {
                terrain_suivant=set_case(boite_courant->terrain,promptCoup(),symbole_courant);
                 tour=-1;
            }
            else
            {
                terrain_suivant = set_case(boite_courant->terrain,ProchainCoup(),symbole_courant);
                tour=1;
            }
            for (i=0; i < nb_case_libre(terrain_suivant);i++)
            {
                if(verify_sym(terrain_suivant,boite_courant->suivants[i]->terrain))
                       boite_courant=boite_courant->suivants[i];
            }


            changerSymbole(symbole_courant);

        }
        if((partieFinie(boite_courant->terrain)==ROND & test== 0) | (partieFinie(boite_courant->terrain)==CROIX & test==1))
        {
            modifier_billes(boite_courant);//cas ou joueur gagne
        }
        else
        {
          modifier_billes(boite_courant);//cas ou IA gagne
        }
    }

    else
    {
        for(compteur=0;compteur<choixjoueur;compteur++)
        {
            //debut d'une partie IA contre IA
            while(partieFinie(boite_courant->terrain)==0)
            {

            }
        }
    }
    choixjoueur = promptGamemode();
}
}
