#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sqlite3.h>
#include <string.h>

int menu(int entre);
void debuffer();
void debufferTeller();
int newAccount();

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
    system("clear");                                                                                                  // Sur linux cela sera la commande clear
    printf("\t\tSysteme de management bancaire\n\n\t\t░░░░░░░░░░ Bienvenue dans le menu principal ░░░░░░░░░░\n"); // En-tete
    printf("1. Creer un nouveau compte\n2. Mettre a jour un nouveau compte\n3. Effectuer des transactions\n4. Verifier les details d'un compte existant\n5. Supprimer un compte existant\n6. Lister les clients de la banques\n7. Quitter l'application");
    
    /*
        Avec les problemes de buffer il faut vider notre buffer a chaque fois que l'on retourne 
        dans le menu du coup pour eviter que l'on voit appuyer sur entrer pour commencer et que
        l'on commence sans pouvoir appuyer sur entree voici la parade
    */
    if (entre == 0)
    {
        printf("\n\nAppuyer sur entrer pour commencer");
    }

    debuffer();
    printf("\n\n\n\nEntrer votre choix : ");
    scanf("%c", &buffer);
    debuffer();

    // Verification de choice pour eviter des bugs
    
    //On verifie en premier que l'on a rentrer un chiffre
    if (!isdigit(buffer))
    {
        printf("Un numero a ete demande");
        printf("\n\n\n\nEntrer votre choix : ");
        scanf("%c", &buffer);
        debuffer();
    }

    choice = buffer - '0';

    // Action selon le numero choisis
    switch (choice)
    {
    case 1:
        printf("Creation d'un nouveau comptre");
        newAccount();
        break;

    case 2:
        printf("Mise a jour d'un compte");
        scanf("%d", &temp);
        break;

    case 3:
        printf("Effectuer des transactions");
        scanf("%d", &temp);
        break;

    case 4:
        printf("Verifier les details d'un compte existant");
        scanf("%d", &temp);
        break;

    case 5:
        printf("Supprimer un compte existant");
        scanf("%d", &temp);
        break;

    case 6:
        printf("Lister les clients de la banques");
        scanf("%d", &temp);
        break;

    case 7:
        printf("Quitter");
        exit(0);
        break;

    default:
        // Bien joue mon hackeur cadeau nutella
        printf("Mauvais choix de numero");
        exit(-1);
        break;
    }

    return temp;
}

void debuffer(){
    while (getchar() != '\n');
}

void debufferTeller(){
    printf("Appuyer sur entree pour continuer\n");
    debuffer();
}

/*
    Fonction pour creer un nouveau compte on va se connecter a notre base de donnees qui contient
    deja nos tables deja parametrer, donc cette fonction va seulement permttre d'ajouter des entree dans
    la table utilisateurs
*/

int newAccount() {
    system("clear");
    sqlite3 *db;
    int rc = sqlite3_open("bank.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        return 1;
    }

    //Definition des variables du compte
    int  numero, solde, choixAcc = 0;
    char nom[64] = "";
    char prenom[64] = "";
    char dateBirth[32] = "";
    char typeAcc[32] = "";
    char nationalite[32] = "";

    //Insertion des valeurs dans les variables
    printf("\n\t\t░░░░░░░░░░ Creation d'un nouveau compte ░░░░░░░░░░\n");
    printf("Veuillez remplir les champs suivants avec vos informations personnelles\n\n");
    printf("Quels est le type de compte : \n1- Compte Courant\n2- Compte Epargne\n3- Compte bloque 1 an\n4- Compte bloque 2 ans\n5- Compte bloquer 3 ans\n\t\tUn choix errone entraine la creation d'un compte courant\n");
    scanf("%d",&choixAcc);
    switch (choixAcc)
    {
    case 1:
        strcpy(typeAcc, "Courant");
        break;

    case 2:
        strcpy(typeAcc, "Epargne");
        break;

    case 3:
        strcpy(typeAcc, "Bloque1");
        break;

    case 4:
        strcpy(typeAcc, "Bloque2");
        break;

    case 5:
        strcpy(typeAcc, "Bloque3");
        break;

    default:
        strcpy(typeAcc, "Compte Courant");
        break;
    }

    debufferTeller();

    printf("\nVotre nom : ");
    scanf("%s",nom);

    debufferTeller();

    printf("\nVotre prenom : ");
    scanf("%s",prenom);

    debufferTeller();

    printf("\nVotre date de naissance : ");
    scanf("%s",dateBirth);

    debufferTeller();

    printf("\nVotre numero de telephone : ");
    scanf("%d", &numero);

    debufferTeller();

    printf("\nVotre date nationnalite : ");
    scanf("%s", nationalite);

    debufferTeller();

    printf("\nCombien deposez vous pour votre premier depots : ");
    scanf("%d", &solde);

    debufferTeller();

    //Maintenant on passe a l'ecriture dans la base de donnees
    char sql[2000];
    snprintf(sql, sizeof(sql), "INSERT INTO users (Nom, Prenom, DateNaissance, Nationalite, NumeroTelephone, Solde, Type) VALUES ('%s', '%s', '%s', '%s', '%d', '%d', '%s');", nom, prenom,dateBirth,nationalite,numero,solde,typeAcc);

    rc = sqlite3_exec(db, sql, 0, 0, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de l'insertion des données : %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Données insérées avec succès.\n");
    }

    sqlite3_close(db);

    return 0;

}