#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int menu(int entre);
void debuffer();

int main(int argc, char const *argv[])
{
    int entre = 0;
    while (1)
    {
        menu(entre);
        entre++;
    }
    
    return 0;
}

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
int menu(int entre)
{
    int choice, temp;
    char buffer = '@';
    system("cls");                                                                                                  // Sur linux cela sera la commande clear
    printf_s("\t\tSysteme de management bancaire\n\n\t\t░░░░░░░░░░ Bienvenue dans le menu principal ░░░░░░░░░░\n"); // En-tete
    printf_s("1. Creer un nouveau compte\n2. Mettre a jour un nouveau compte\n3. Effectuer des transactions\n4. Verifier les details d'un compte existant\n5. Supprimer un compte existant\n6. Lister les clients de la banques\n7. Quitter l'application");
    
    /*
        Avec les problemes de buffer il faut vider notre buffer a chaque fois que l'on retourne 
        dans le menu du coup pour eviter que l'on voit appuyer sur entrer pour commencer et que
        l'on commence sans pouvoir appuyer sur entree voici la parade
    */
    if (entre == 0)
    {
        printf_s("\n\nAppuyer sur entrer pour commencer");
    }

    debuffer();
    printf_s("\n\n\n\nEntrer votre choix : ");
    scanf_s("%c", &buffer);
    debuffer();

    // Verification de choice pour eviter des bugs
    
    //On verifie en premier que l'on a rentrer un chiffre
    if (!isdigit(buffer))
    {
        printf("Un numero a ete demande");
        printf_s("\n\n\n\nEntrer votre choix : ");
        scanf_s("%c", &buffer);
        debuffer();
    }

    choice = buffer - '0';

    // Action selon le numero choisis
    switch (choice)
    {
    case 1:
        printf_s("Creation d'un nouveau comptre");
        scanf_s("%d", &temp);
        break;

    case 2:
        printf_s("Mise a jour d'un compte");
        scanf_s("%d", &temp);
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
        // Bien joue mon hackeur cadeau nutella
        printf_s("Mauvais choix de numero");
        exit(-1);
        break;
    }

    return temp;
}

void debuffer(){
    while (getchar() != '\n');
}