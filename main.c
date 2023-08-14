#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include "utilitaire.h"

int menu(int entre);
int newAccount();
int updateAccount();
int verifAcc();
int listAcc();

static int callback(void *data, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static int callbackCheck(void *flag, int argc, char **argv, char **azColName)
{
    int *callback_flag = (int *)flag;
    *callback_flag = 1; // Mettre le flag à 1 si un résultat est trouvé
    return 0;
}

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
        newAccount();
        break;

    case 2:
        updateAccount();
        break;

    case 3:
        printf("Effectuer des transactions");
        scanf("%d", &temp);
        break;

    case 4:
        verifAcc();
        break;

    case 5:
        printf("Supprimer un compte existant");
        scanf("%d", &temp);
        break;

    case 6:
        listAcc();
        break;

    case 7:
        system("clear");
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
    char typeAcc[32] = "";
    char dateBirth[32] = "";
    char nationalite[32] = "";
    char numerotemp[32] = "";
    char soldetemp[32] = "";
 
    //Insertion des valeurs dans les variables cela va etre une boucle s'il y a une erreur on recommence
    printf("\n\t\t░░░░░░░░░░ Creation d'un nouveau compte ░░░░░░░░░░\n");
    printf("Veuillez remplir les champs suivants avec vos informations personnelles (si vous avez fait une erreur vous pouvez recommencez a la fin du formulaire)\n\n");

    //Debut boucle informations
    int valide = 0;
    while (valide == 0){
        printf("Quels est le type de compte : \n1- Compte Courant\n2- Compte Epargne\n3- Compte bloque 1 an\n4- Compte bloque 2 ans\n5- Compte bloquer 3 ans\n\t\tUn choix errone entraine la creation d'un compte courant\n");
        scanf("%d", &choixAcc);
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
        scanf("%s", nom);

        debufferTeller();

        printf("\nVotre prenom : ");
        scanf("%s", prenom);

        debufferTeller();

        printf("\nVotre date de naissance (DD-MM-YYYY) ");
        char *dateBirthh = dateBIrth();

        debufferTeller();

        char contexte[64] = "numero de telephone";
        numero = verifNumero(numerotemp, contexte);

        debufferTeller();

        printf("\nVotre date nationnalite : ");
        scanf("%s", nationalite);

        debufferTeller();

        strcpy(contexte, "solde du compte");
        solde = verifNumero(soldetemp, contexte);

        debufferTeller();

        printf("\n\n\t\t░░░░░░░░░░ Recapaputilatif de vos informations personnelle░░░░░░░░░░\n");
        printf("Nom\t : %s\nPrenom\t: %s\nDate de Naissance\t: %s\nNumero\t: %d\nNationnalite\t: %s\n\n",nom,prenom,dateBirthh,numero,nationalite);
        printf("Type\t: %s\nSolde\t:%d",typeAcc,solde);
        printf("\nValidez vous vos informations ?(Y/N)");
        char validation;
        scanf("%c",&validation);
        if(validation != 'Y'){
            system("clear");
            continue;
        }
        else
        {
            strcpy(dateBirth,dateBirthh);
            valide = 1;
        }
    }
    
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

    //On donne a l'utilisateur son id
    printf("Voici votre identifiant : ");
    char readsql[2000];
    snprintf(readsql, sizeof(readsql), "SELECT id FROM users WHERE Nom = '%s' AND Prenom = '%s';",nom,prenom);
    rc = sqlite3_exec(db, readsql, callback, 0, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la lecture des données : %s\n", sqlite3_errmsg(db));
    }

    sleep(3);

    sqlite3_close(db);

    return 0;

}

/*
    La fonction update account va permettre de changer les informations qui sont succeptible d'etre changer
    pour rappel un compte est composer de Nom, Prenom, DateNaissance,Nationalite,NumeroTelephone*,Solde*,Type
    Dans cette les variable qui peuvent changer ont une apostrophe pour le solde les changement vont se faire
    avec les transaction du coup cette fonction va permettre de changer le numero de telephone
    Pour se faire on va demander l'id du client on va d'abord verifier si le client exite si c'est le cas on
    lui demande son nouveau numero on verifie que c'est bien un numero et on le change
*/

int updateAccount()
{
    system("clear");
    sqlite3 *db;
    int rc = sqlite3_open("bank.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sleep(3);
        return 1;
    }

    // Dialogue pour verifier l'existance du client
    int idAcc;
    char idAcc_verif[32] = "";
    idAcc = verifNumero(idAcc_verif,"ID du compte");

    int callback_flag = 0;
    char verifID[200];

    snprintf(verifID, sizeof(verifID), "SELECT ID FROM users WHERE ID = %d;", idAcc);

    rc = sqlite3_exec(db,verifID,callbackCheck,&callback_flag,0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la vérification de l'ID : %s\n", sqlite3_errmsg(db));
        sleep(3);
    }
    else
    {
        if (callback_flag)
        {
            printf("L'ID existe dans la base de données.\n");
            char updateID[200];
            int numero;
            char numeroTemp[32] = "";
            char contexte[64] = "numero de telephone";
            numero = verifNumero(numeroTemp, contexte);

            snprintf(updateID, sizeof(updateID), "UPDATE users SET NumeroTelephone = '%d' WHERE ID = '%d'",numero, idAcc);
            rc = sqlite3_exec(db,updateID,0,0,0);

            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Erreur lors de la mise à jour du numéro de téléphone : %s\n", sqlite3_errmsg(db));
                sleep(3);
            }
            else
            {
                printf("Numéro de téléphone mis à jour avec succès.\n");
                sleep(3);
            }
            sqlite3_close(db);
        }
        else
        {
            printf("L'ID n'existe pas dans la base de données.\n");
            sleep(3);
            sqlite3_close(db);
            return -1;
        }
    }

    sqlite3_close(db);

    return 0;
}

/*
    Cette fonction permet de voir tous les details d'un compte
*/

int verifAcc()
{
    system("clear");
    sqlite3 *db;
    int rc = sqlite3_open("bank.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sleep(3);
        return 1;
    }

    int idAcc;
    char idAcc_verif[32] = "";
    idAcc = verifNumero(idAcc_verif, "ID du compte");

    int callback_flag = 0;
    char verifID[200];

    snprintf(verifID, sizeof(verifID), "SELECT ID FROM users WHERE ID = %d;", idAcc);

    rc = sqlite3_exec(db, verifID, callbackCheck, &callback_flag, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la vérification de l'ID : %s\n", sqlite3_errmsg(db));
        sleep(3);
    }
    else
    {
        if (callback_flag)
        {
            printf("L'ID existe dans la base de données.\n");
            char readsql[200];
            snprintf(readsql,sizeof(readsql), "SELECT * FROM users WHERE ID = %d", idAcc);

            rc = sqlite3_exec(db,readsql, callback,0,0);

            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Erreur lors de la sélection : %s\n", sqlite3_errmsg(db));
                sleep(3);
            }

            sqlite3_close(db);
            char sortie = 'N';
            do
            {
                printf("Voulez vous sortir (Y/N)\n");
                scanf("%c",&sortie);
                sleep(3);
            } while (sortie != 'Y');
            
        }
        else
        {
            printf("L'ID n'existe pas dans la base de données.\n");
            sleep(3);
            sqlite3_close(db);
            return -1;
        }
    }

    sqlite3_close(db);
}

int listAcc()
{
    system("clear");
    //Jolie petit affichage
    printf("\t\t\t░░░░░░░░░░ Liste des clients de la banque ░░░░░░░░░░\n\n\n");

    sqlite3 *db;
    int rc;

    // Ouvrir la base de données
    rc = sqlite3_open("bank.db", &db);
    if (rc)
    {
        fprintf(stderr, "Erreur lors de l'ouverture de la base de données : %s\n", sqlite3_errmsg(db));
        sleep(3);
        return 1;
    }

    // Requête SQL pour sélectionner toutes les colonnes de toutes les lignes
    const char *selectQuery = "SELECT Nom,Prenom,Nationalite FROM users;";

    rc = sqlite3_exec(db, selectQuery, callback, 0, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de la sélection : %s\n", sqlite3_errmsg(db));
    }

    // Fermer la base de données
    sqlite3_close(db);

    char sortie;
    debufferTeller();
    do
    {
        printf("Voulez vous sortir (Y/N)\n");
        scanf("%c", &sortie);
    } while (sortie != 'Y');

    return 0;
}