#include "CLI.h"

char* login(){

    // static pour que la variable name persiste
    // dans le cas ou on a pas static la valeur de la variable a des chance de disparaitre apres que la fonction finie de s'executer
    static char name[40];

    printf("[*] Saisir nom d'utilisateur :");
    scanf("%39s",name);

    return name;

}

void showCommands(){
    printf("[*] Commandes Disponibles : \n");
    for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
        printf("\t- %s : %s \n",commands[i][0], commands[i][1]);
    }
}

void addProductCLI(char* args, char* username){

    Product p;
    FILE* datacsv = initCSV("data.csv", "a+");
    strcpy(p.userName, username);
    p.ID = calcNextID();

    // parsing des arguments
    // on separe les arguments en plusieurs valeur pour remplir la structure
    int result = sscanf(args, "%39[^ ] %f %i %f %i/%i/%i %i/%i/%i",
           p.nameP,
           &p.unitPrice,
           &p.qtStock,
           &p.thresholdAlert,
           &p.lastEntry.d,&p.lastEntry.m,&p.lastEntry.y,
           &p.lastExit.d,&p.lastExit.m,&p.lastExit.y
           );

    // on verifie si on a bien recuperer tout les arguments ont etait sauvegarer
    if (result == 10){
        saveProductToCSV(p,datacsv);
        printf("[*] Produit ajouter avec succes (ID = %i).\n",p.ID);
    } else {
        printf("[!] Erreur l'hors de la sauvegarde du produit ( argument manquant ou format incorrect ).\n");
    }

    fclose(datacsv);

}

void showProductCLI(){

    printf("ID\tProduit\t  Utilisateur\tPrix Unitaire\tStock\tSeuil Alerte\tDate Derniere Entree\t Date Derniere Sortie\n");

    FILE* datacsv = initCSV("data.csv","r");
    Product p;

    while (!feof(datacsv)){
        fetchProductFromCSV(&p, datacsv);

        printf("%i\t%s %s\t\t%.3f\t\t%i\t%.3f\t\t%i/%i/%i\t\t\t %i/%i/%i\n",
               p.ID,
               p.nameP,
               p.userName,
               p.unitPrice,
               p.qtStock,
               p.thresholdAlert,
               p.lastEntry.d, p.lastEntry.m, p.lastEntry.y,
               p.lastExit.d, p.lastExit.m, p.lastExit.y
        );
    }

    fclose(datacsv);

}

void rmProductClI(char* args){

    FILE* datacsv = initCSV("data.csv","r");
    int N = calcNextID();
    Product T[N];

    for (int i = 0; i < N; i++){
        fetchProductFromCSV(&T[i], datacsv);
    }
    fclose(datacsv);

    datacsv = initCSV("data.csv","w");
    for (int i = 0; i < N; i++){
        if (T[i].ID != atoi(args)){
            if (T[i].ID > atoi(args)){
                T[i].ID--;
            }
            saveProductToCSV(T[i], datacsv);
        }
    }

    fclose(datacsv);

}

void searchProductCLI(char* args){

    FILE* datacsv = initCSV("data.csv","r");
    char* parsedArgs = strtok(args, " ");
    Product p;

    if ( !strcmp(parsedArgs,"ID") ){
        printf("ID\tProduit\t  Utilisateur\tPrix Unitaire\tStock\tSeuil Alerte\tDate Derniere Entree\t Date Derniere Sortie\n");
        parsedArgs = strtok(NULL, " ");
        while (!feof(datacsv)){
            fetchProductFromCSV(&p, datacsv);
            if (p.ID == atoi(parsedArgs)){
                printf("%i\t%s %s\t\t%.3f\t\t%i\t%.3f\t\t%i/%i/%i\t\t\t %i/%i/%i\n",
                       p.ID,
                       p.nameP,
                       p.userName,
                       p.unitPrice,
                       p.qtStock,
                       p.thresholdAlert,
                       p.lastEntry.d, p.lastEntry.m, p.lastEntry.y,
                       p.lastExit.d, p.lastExit.m, p.lastExit.y
                );
            }
        }
    } else if (!strcmp(parsedArgs,"NOM")){
        printf("ID\tProduit\t  Utilisateur\tPrix Unitaire\tStock\tSeuil Alerte\tDate Derniere Entree\t Date Derniere Sortie\n");
        parsedArgs = strtok(NULL, " ");
        while (!feof(datacsv)){
            fetchProductFromCSV(&p, datacsv);
            if (!strcmp(parsedArgs, p.nameP)){
                printf("%i\t%s %s\t\t%.3f\t\t%i\t%.3f\t\t%i/%i/%i\t\t\t %i/%i/%i\n",
                       p.ID,
                       p.nameP,
                       p.userName,
                       p.unitPrice,
                       p.qtStock,
                       p.thresholdAlert,
                       p.lastEntry.d, p.lastEntry.m, p.lastEntry.y,
                       p.lastExit.d, p.lastExit.m, p.lastExit.y
                );
            }
        }

    } else {
        printf("[!] Argument manquant ou inadequat !\n");
    }

    fclose(datacsv);

}

void editProductCLI(char* args, char* username){

    FILE* datacsv = initCSV("data.csv","r");
    int N = calcNextID();
    Product T[N], newP;
    char editArg[MAX_ARG_SIZE];

    for (int i = 0; i < N; i++){
        fetchProductFromCSV(&T[i], datacsv);
    }
    fclose(datacsv);

    printf("[*] Entrez les nouvelles proprietes du produit.\n>");
    gets(editArg);

    int result = sscanf(editArg, "%39[^ ] %f %i %f %i/%i/%i %i/%i/%i",
                        newP.nameP,
                        &newP.unitPrice,
                        &newP.qtStock,
                        &newP.thresholdAlert,
                        &newP.lastEntry.d,&newP.lastEntry.m,&newP.lastEntry.y,
                        &newP.lastExit.d,&newP.lastExit.m,&newP.lastExit.y
    );

    if (result == 10){
        datacsv = initCSV("data.csv","w");
        for (int i =0; i<N; i++){
            if (T[i].ID == atoi(args)){
                newP.ID = T[i].ID;
                strcpy(newP.nameP, username);
                T[i] = newP;
            }
        }
        for (int i = 0; i < N; i++){
            saveProductToCSV(T[i], datacsv);
        }
        fclose(datacsv);
    } else {
        printf("[!] Not enough or wrong format argument !\n");
    }

    // /!\ probleme pour copier le nouveau nom du produit
    // solution : copier automatiquement les nouvelle donnees sans passer par une struct temporaire
    // a faire

}

void CLI(char* name){
    printf("\n\n");
    printf("[*] Bienvenu(e) %s\n",name);
    printf("[*] utilisez 'help' pour avoir la liste de commandes.\n");

    // boucle saisie de commande
    char input[MAX_INPUT_SIZE], args[MAX_ARG_SIZE],lastCommand[MAX_ARG_SIZE];

    do {
        printf(">");
        gets(input);
        // on separe l'input de l'utilisateur en 2 parties
        // la premiere est le nom de la commande et c'est avec qu'on verifie quelle commande il a utiliser
        // et la deuxieme partie est composer d'arguments qui sont utiliser pour le fonctionnement de celle-ci
        // pour l'argument on recupere la chaine jusqu'a arriver au retour a la ligne cad "\n"
        sscanf(input, "%s %[^\n]", lastCommand, args);
        if (!strcmp(lastCommand,"help")){
            showCommands();
        } else if (!strcmp(lastCommand,"add")){
            addProductCLI(args, name);
        } else if (!strcmp(lastCommand,"edit")){
            editProductCLI(args, name);
        } else if (!strcmp(lastCommand,"rm")){
            rmProductClI(args);
        } else if (!strcmp(lastCommand,"list")){
            showProductCLI();
        } else if (!strcmp(lastCommand,"sr")){
            searchProductCLI(args);
        }else if (!strcmp(lastCommand,"sort")){
            //sortProductCLI();
        }
    } while(strcmp(lastCommand, "exit")); // on quitte le programme quand l'utilisateur entre "exit"

}