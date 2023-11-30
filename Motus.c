#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET "\x1B[0m"

// La fonction pour supprimer un mot du fichier
void deleteWordFromFile(const char *filename, const char* wordToDelete) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Supprime le caract?re de nouvelle ligne ? la fin de la ligne lue
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, wordToDelete) != 0) {
            fputs(line, tempFile);
            /*fputc('\n', tempFile);*/  // R??crit la nouvelle ligne
        }}
    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0) {
        perror("Erreur lors de la suppression du fichier d'origine");
    }

    if (rename("temp.txt", filename) != 0) {
        perror("Erreur lors du renommage du fichier temporaire");
    }
}

// Fonction pour cr?er un fichier
void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de la cr?ation du fichier");
        exit(1);
    }
    fclose(file);
    printf("Fichier '%s' a ?t? cr?? avec succ?s.\n", filename);}
//existance dans fichier
int motExistePasDansFichier(const char *nomFichier, const char*  motRecherche) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1; // Code d'erreur
    }

    char ligne[100]; // Taille arbitraire pour stocker une ligne du fichier
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Recherche du mot dans la ligne
        if (strstr(ligne, motRecherche) != NULL) {
            fclose(fichier);
            return 0; // Le mot existe d?j? dans le fichier
        }
    }

    fclose(fichier);
    return 1; // Le mot n'existe pas dans le fichier
}
// choix du niveau
const char* Niveau() {
    char reponse[3];

    printf("Choisissez le niveau : facile (0), moyen (1) ou difficile (2) : ");
    scanf("%2s", reponse);

    if (strcmp(reponse, "0") == 0) {
        return "easy.txt";
    } else if (strcmp(reponse, "1") == 0) {
        return "medium.txt";
    } else if (strcmp(reponse, "2") == 0) {
        return "hard.txt";
    } else {
        printf("Niveau non valide. Utilisation du niveau facile par défaut.\n");
        return "easy.txt";
    }
}

//detectation du niveau
const char* fichierNiveau(const char *mot) {
    if (strlen(mot) <= 4) {
        return "easy.txt";
    } else if (strlen(mot) == 5 || strlen(mot) == 6) {
        return "medium.txt";
    } else if (strlen(mot) > 6) {
        return "hard.txt";
    }
    return NULL;
}

//ajouter mots au fichier
void appendWordsToFile(const char *fileName, const wordList[], int numWords) {
    FILE *file = fopen(fileName, "a"); // Ouvrir le fichier en mode "ajout"
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numWords; i++) {
        fprintf(file, "%s\n", wordList[i]);
    }

    fclose(file);
}
// si le fichier est vide
int isFileEmpty(const char *filename) {
    FILE *file = fopen(filename, "r");
    int isEmpty = 0;

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            isEmpty = 1;
        }

        fclose(file);
    }

    return isEmpty;
}
void main()
{    int score;
    char jouer_autre_fois;
    printf("                                       Bienvenue au jeu Motus!\n");
    // 3 fichier de 5 mots chacun symbolise les niveaux du jeue
    const char* additionalWordsEasy[] = {"chat","fort","cour","jour","joue"};
    const char* additionalWordsMoyen[] = {"arbre","for?t","courir","voyage","jouer"};
    const char* additionalWordsDifficile[] = {"compliqu?","palastin","tunisie","symphonie","capturer"};
    /* createFile("easy.txt");
      createFile("medium.txt");
      createFile("hard.txt");*/
    /* appendWordsToFile("easy.txt", additionalWordsEasy, 5);
     appendWordsToFile("medium.txt", additionalWordsMoyen, 5);
     appendWordsToFile("hard.txt", additionalWordsDifficile, 5);*/
    char user[2];
    printf("?tes-vous un administrateur ou un joueur ? (0/1) : ");
    scanf("%s", user);
    if (strcmp(user, "0") == 0)
    {char ans[3];
        const char* mot[50];
        printf("Voulez-vous ajouter (aj) ou supprimer (s) un mot  ? (ou 'q' pour sortir)\n");
        do {
            scanf("%s", ans);
            if (strcmp(ans, "aj") == 0) {
                printf("Quel mot voulez-vous ajouter ?\n");
                scanf("%s", mot);
                const char* nomFichier = fichierNiveau(mot);
                FILE *fichier = fopen(nomFichier, "a");
                if (fichier != NULL) {
                    /*char mot[50];*/
                    int resultat = motExistePasDansFichier(nomFichier, mot);
                    if (resultat == 1) {
                        fprintf(fichier, "%s\n", mot);
                        printf("Le mot '%s' a ?t? ajout? au fichier.\n", mot);
                        fclose(fichier);}
                    else if (resultat == 0) {
                        printf("Le mot \"%s\" existe d?j? dans le fichier.\n", mot);}
                }}

            else if (strcmp(ans, "s") == 0) {
                printf("Quel mot voulez-vous supprimer ?\n");
                scanf("%s", mot);
                const char *nomFichier = fichierNiveau(mot);
                FILE *fichier = fopen(nomFichier, "a");

                if (fichier == NULL){
                    perror("Erreur lors de l'ouverture du fichier");
                    }
                const char * mot[50];
                int resultat = motExistePasDansFichier(fichier, mot);
                if (resultat == 0) {

                    /*   FILE *fichier = fopen("%s",Niveau(), "r");

                        if (fichier == NULL) {
                          perror("Erreur lors de l'ouverture du fichier");
                          return 1;}

                         char const * caractere;

                         while ((caractere = fgetc(fichier)) != EOF) {
                          putchar(caractere);
                           }

                         //fclose(fichier);*/
                    deleteWordFromFile( fichier, mot);
                    printf("Le mot '%s' a ?t? supprim? de fichier.\n", mot);
                }
                else if (resultat == 1) {
                    printf("Le mot \"%s\" n'existe pas d?j? dans le fichier.\n", mot);}
                fclose(fichier);}

            else if (strcmp(ans, "q") == 0) {
                break;}
            else {
                printf("Choix non valide.\n");}
        } while (1);
    }
    int jouer;
    printf("Voulez-vous jouer ? (1 = Oui / 0 = Non) : ");
    scanf("%d", &jouer);
    do{
        if (jouer)
        {strcpy(user, "1");
            char * MOT_SECRET;
            char ligne[256];
            char s;
            char* hh;
            /* hh = (char*)malloc(15*sizeof(char));
              hh = Niveau
              printf("niveau : %s",Niveau())
      */
            FILE *fichier=fopen(Niveau(), "r");
            if (fichier == NULL) {
                perror("Le fichier est vide.");
                }

            int numLines = 0;
            while (fgets(ligne, sizeof(ligne), fichier) != NULL) {numLines++;}
            fclose(fichier);
            srand(time(NULL));
            int randomLine = rand() % numLines;

            for (int i = 0; i <= randomLine; i++) {fgets(MOT_SECRET, sizeof(MOT_SECRET), fichier);}
            fclose(fichier);
            MOT_SECRET[strcspn(MOT_SECRET, "\n")] = '\0';
            if (strcmp(user, "1") == 0){
                char motj[25];
                int t, l, i;
                l = strlen(MOT_SECRET);
                char nb;
                printf ("Voulez-vous jouer en bin?me(2) ou en mon?me(1)");
                scanf("%s",nb);

                printf("                                            \\\\  //");
                printf("\n                                             \\\\//  \n");
                printf("                                              \\/  \n");

                printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
                printf("\n Le mot secret a %d lettres", l);
                t = 0;
                char a[l];
                do{for(i=0;i<nb;i++)
                    {printf("\n joueur #%d : \n %c\t ", nb+1);
                        printf("\n Proposition #%d : \n %c\t ", t + 1,MOT_SECRET[0]);
                        scanf("%s", motj);
                        if (strlen(motj) != l-1) {
                            printf("       ........................        \n Le mot doit avoir exactement %d lettres.\n", l);
                            continue;
                        }printf( "\t%c\t" ,MOT_SECRET[0]);
                        for (i = 0; i < l - 1; i++) {
                            if (motj[i] == MOT_SECRET[i + 1]) {printf(GREEN "\t%c\t" RESET, motj[i]);}
                            else {
                                int found = 0; // Variable pour indiquer si le caract?re a ?t? trouv? dans MOT_SECRET
                                for (int j = 0; j < l - 1; j++) {
                                    if (motj[i] == MOT_SECRET[j + 1]) {
                                        printf(YELLOW "\t%c\t" RESET, motj[i]);
                                        found = 1; // Le caract?re a ?t? trouv?
                                        break;}}
                                if (!found) {printf(RED "\t%c\t" RESET, motj[i]);}}}
                        t++;
                        strncpy(a, MOT_SECRET + 1, l-1);
                        a[l-1] = '\0';}
                } while (strcmp(motj, a) != 0);
                printf("\nBravo ! Vous avez devin? le mot *** %s *** en %d essais.\n", MOT_SECRET, t);
                deleteWordFromFile(fichier,MOT_SECRET );}
            if (isFileEmpty(fichier)){
                if (strcmp(fichier, "easy.txt") == 0)
                {appendWordsToFile(fichier, additionalWordsEasy, 5);}
                else if (strcmp(fichier, "medium.txt") == 0)
                { appendWordsToFile(fichier, additionalWordsMoyen, 5);}
                else if (strcmp(fichier, "hard.txt") == 0)
                {appendWordsToFile(fichier, additionalWordsDifficile, 5);}}

            printf("Voulez-vous jouer une autre fois ? (1 = Oui / 0 = Non) : ");
            scanf(" %c", &jouer_autre_fois);
        } else {printf("Vous ne jouez pas.");}
    }while (jouer_autre_fois == '1');
}
