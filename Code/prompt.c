int promptPremierJoueur()
{


int32_t i=-1;
     while(i!= 1 & i !=0)
        {
            printf("Qui commence?\n0:Vous\n1:l'IA\n");
            scanf("%d,&i");
        }
    return i;
}
