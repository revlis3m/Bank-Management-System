#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utilitaire.h"

void debuffer()
{
    while (getchar() != '\n')
        ;
}

void debufferTeller()
{
    printf("Appuyer sur entree pour continuer\n");
    debuffer();
}

int verifNumero (char* chaine,char* contexte){
    char input[100]; // Chaîne de caractères pour stocker l'entrée de l'utilisateur
    strcpy(input, contexte);
    int chiffre;
    int verif = 1;

    do
    {
        printf("Veuillez saisir uniquement des chiffres.\n");
        debufferTeller();
        printf("Veuillez entrer le %s : ",contexte);
        scanf("%s", input);

        // Vérifier si chaque caractère de l'entrée est un chiffre
        int i = 0;
        while (input[i] != '\0')
        {
            if (!isdigit(input[i]))
            {
                printf("Entrée invalide. Veuillez saisir uniquement des chiffres.\n");
                verif = -1;
            }
            else
            {
                verif = 1;
            }
            i++;
        }
        if (verif != -1)
        {
            verif = 0;
        }
        
    } while (verif == -1);

    // Convertir la chaîne en entier à l'aide de la fonction atoi
    chiffre = atoi(input);

    return chiffre;
}


int is_valid_date(const char *date)
{
    if (strlen(date) != 10)
    {
        return 0; // La longueur de la date doit être exactement 10 caractères (dd-mm-yyyy)
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            if (date[i] != '-')
            {
                return 0; // Les tirets doivent être aux positions 2 et 5
            }
        }
        else if (!isdigit(date[i]))
        {
            return 0; // Les autres caractères doivent être des chiffres
        }
    }

    return 1; // La date est valide
}

char* dateBIrth ()
{
    char *dateBirth = (char *)malloc(12 * sizeof(char)); // Allouer de la mémoire

    if (dateBirth == NULL)
    {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    do
    {
        printf("Veuillez entrer une date au format dd-mm-yyyy : ");
        scanf("%s", dateBirth);

        if (!is_valid_date(dateBirth))
        {
            printf("Format de date incorrect. Veuillez saisir une date au format dd-mm-yyyy.\n");
            continue;
        }
    } while (!is_valid_date(dateBirth));

    printf("Date de naissance valide : %s\n", dateBirth);

    return dateBirth;
}
