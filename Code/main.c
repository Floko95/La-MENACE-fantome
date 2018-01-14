
//....
choix_graphe();
int32_t choixjoueur = promptGamemode();
uint32_t terrain;
uint8_t symbole_courant,tour;
uint32_t compteur,test;
while(choixjoueur != -1)
{
    terrain=0;
    if(choixjoueur==0)
    {
        //debut d'un partie
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
        while(partieFinie(terrain)==0)
        {
            if(tour==1)
            {
                set_case(terrain,promptCoup(),symbole_courant);
                tour=-1;
            }
            else
            {
                set_case(terrain,ProchainCoup(),symbole_courant);//??
                //modifier bits de bille à 1
                tour=1;
            }
            changerSymbole(symbole_courant);
        }
        if((partieFinie(terrain)==ROND & test== 0) | (partieFinie(terrain)==CROIX & test==1))
        {
            //cas ou joueur gagne
        }
        else
        {
          //cas ou IA gagne
        }
    }

    else
    {
        for(compteur=0;compteur<choixjoueur;compteur++)
        {
            //debut d'une partie IA contre IA
            while(partieFinie(terrain)==0)
            {

            }
        }
    }
    choixjoueur = promptGamemode();
}
