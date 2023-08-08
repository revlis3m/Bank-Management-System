#include <stdio.h>
#include <stdlib.h>
#include "heart.h"

/*
    Notre menu va etre lu dans une boucle infini et quand l'on va y rentrer apres l'affichage on pourra choisir
    notre action, on va verifier si l'action est dans la liste des choix que l'on va definir
    1. Creer un nouveau compte
    2. Mettre a jour un nouveau compte
    3. Effectuer des transactions
    4. Verifier les details d'un compte existant
    5. Supprimer un compte existant
    6. Lister les clients de la banques
    7. Quitter l'application
    Si le choix n'est pas dans la liste on notifie que le choix est errone on retourne dans le menu en surlignant la ligne exit
    A chaque fois que le menu est appeler l'ecran est vide en premier pour effacer ce qu'il y avait avant d'afficher le menu (securite)
*/
int menu () {
    int choice,temp;
    system("cls"); //Sur linux cela sera la commande clear
    printf_s("\t\tSysteme de management bancaire\n\n\t\t░░░░░░░░░░ Bienvenue dans le menu principal ░░░░░░░░░░\n");//En-tete
    printf_s("1. Creer un nouveau compte\n2. Mettre a jour un nouveau compte\n3. Effectuer des transactions\n4. Verifier les details d'un compte existant\n5. Supprimer un compte existant\n6. Lister les clients de la banques\n7. Quitter l'application");
    printf_s("\n\n\n\nEntrer votre choix : ");
    scanf_s("%d",&choice);

    //Verification de choice pour eviter des bugs
    if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
    {
        printf_s("\nNumero invalide\n") ;
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
        {
            printf_s("\tEntrez un bon numero(1,2,3,4,5,6,7) : ");
            scanf_s("%d", &choice);
        }
        
    }
    

    //Action selon le numero choisis
    switch (choice)
    {
    case 1:
        printf_s("Creation d'un nouveau comptre");
        scanf_s("%d", &temp);
        break;

    case 2:
    printf_s("Mise a jour d'un compte");
    scanf_s("%d",&temp);
    break;

    case 3:
        printf_s("Effectuer des transactions");
        scanf_s("%d", &temp);
        break;

    case 4:
        printf_s("Verifier les details d'un compte existant");
        scanf_s("%d", &temp);
        break;

    case 5:
        printf_s("Supprimer un compte existant");
        scanf_s("%d", &temp);
        break;

    case 6:
        printf_s("Lister les clients de la banques");
        scanf_s("%d", &temp);
        break;

    case 7:
        printf_s("Quitter");
        exit(0);
        break;
    
    default:
        //Bien joue mon hackeur cadeau nutella
        printf_s("Mauvais choix de numero");
        exit(-1);
        break;
    }

    return temp;
}