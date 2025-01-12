#include "CLI.h"

void resetCLI(char* name){
    system("cls");
    printf("[*] Bienvenu(e) %s\n",name);
    printf("[*] utilisez 'help' pour avoir la liste de commandes.\n");
}

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
        printf("\t- %s \n\n\t\t-%s \n",commands[i][0], commands[i][1]);
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

void printHeader(){
    printf("%-6s\t%-20s\t%-20s\t%-15s\t%-8s\t%-15s\t%-20s\t%-20s\n",
           "ID", "Produit", "Utilisateur", "Prix Unitaire", "Stock",
           "Seuil Alerte", "Date Derniere Entree", "Date Derniere Sortie");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void printProduct(Product p){
    printf("%-6d\t%-20s\t%-20s\t%-15.2f\t%-8d\t%-15.2f\t%02d/%02d/%-15d\t%02d/%02d/%-2d\n",
           p.ID, p.nameP, p.userName, p.unitPrice, p.qtStock, p.thresholdAlert,
           p.lastEntry.d, p.lastEntry.m, p.lastEntry.y,
           p.lastExit.d, p.lastExit.m, p.lastExit.y);;
}

void showProductCLI(){

    printHeader();

    FILE* datacsv = initCSV("data.csv","r");
    Product p;

    while (!feof(datacsv)){
        fetchProductFromCSV(&p, datacsv);
        // j'arrive pas a trouver une meuilleur maniere de formater
        printProduct(p);
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

    printf("[*] Suppression effectuer avec succes.");

}

void searchProductCLI(char* args){

    FILE* datacsv = initCSV("data.csv","r");
    char* parsedArgs = strtok(args, " ");
    Product p;

    if ( !strcmp(parsedArgs,"ID") ){
        printHeader();
        //separation des arguments
        parsedArgs = strtok(NULL, " ");
        // on cherche l'id
        while (!feof(datacsv)){
            fetchProductFromCSV(&p, datacsv);
            if (p.ID == atoi(parsedArgs)){
                printProduct(p);
            }
        }
    } else if (!strcmp(parsedArgs,"NOM")){
        printHeader();
        //separation des arguments
        parsedArgs = strtok(NULL, " ");
        // on cherche le nom
        while (!feof(datacsv)){
            fetchProductFromCSV(&p, datacsv);
            if (!strcmp(parsedArgs, p.nameP)){
                printProduct(p);
            }
        }

    } else {
        printf("[!] Argument manquant ou inadequat !\n");
    }

    fclose(datacsv);

}

void editProductCLI(char* args, char* username){

    FILE* datacsv = initCSV("data.csv","r");
    int N = calcNextID(); // connaitre le nombre d'element pour cree un tableau de la meme taille
    Product T[N], newP;
    char editArg[MAX_ARG_SIZE];

    for (int i = 0; i < N; i++){
        fetchProductFromCSV(&T[i], datacsv);
    }
    fclose(datacsv);


    datacsv = initCSV("data.csv","w");
    // on cherche le produit avec son ID
    for (int i =0; i<N; i++){
        // quand on le trouve on demande a l'utilisateur
        if (T[i].ID == atoi(args)){

            printf("[*] Entrez les nouvelles proprietes du produit.\n>");
            gets(editArg);

            // on remplie la struct temporaire
            int result = sscanf(editArg, "%39[^ ] %f %i %f %i/%i/%i %i/%i/%i",
                                newP.nameP,
                                &newP.unitPrice,
                                &newP.qtStock,
                                &newP.thresholdAlert,
                                &newP.lastEntry.d,&newP.lastEntry.m,&newP.lastEntry.y,
                                &newP.lastExit.d,&newP.lastExit.m,&newP.lastExit.y
            );

            // on verifie si on a tout les arguemnts
            if ( result == 10){
                newP.ID = T[i].ID;
                strcpy(newP.userName, username);
                // on remplace l'ancienne structure ( produit ) avec la nouvelle
                T[i] = newP;
                for (int i = 0; i < N; i++){
                    // on reecris le fichier data
                    saveProductToCSV(T[i], datacsv);
                }
            } else {
                printf("[!] Arguments manquants ou incorrecte.\n");
            }

            break;
        }
    }
    fclose(datacsv);

    printf("[*] Modification appliquer avec succes.");

    // il existe un meuilleur moyen plus optimise de le faire
    // en copiant et reecrivant que ce qui va suivre le produit qu'on modifie

}

// negatif = d1 plus tot
// positif = d2 plus tot
int compareDate(Date d1, Date d2) {
    if (d1.y < d2.y) {
        return -1;
    } else if (d1.y > d2.y) {
        return 1;
    } else {
        if (d1.m < d2.m) {
            return -1;
        } else if (d1.m > d2.m) {
            return 1;
        } else {
            if (d1.d < d2.d) {
                return -1;
            } else if (d1.d > d2.d) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

    void sortProductCLI(char* args){
    FILE* datacsv = initCSV("data.csv","r");
    int N = calcNextID(); // connaitre le nombre d'element pour cree un tableau de la meme taille
    Product T[N], temp;

    for (int i = 0; i < N; i++){
        fetchProductFromCSV(&T[i], datacsv);
    }
    fclose(datacsv);

    if (!strcmp(args,"PRIX")){
        // trie par prix
        for (int i = N; i > 0; i--){
            for (int j = 1; j < i; j++){
                if ( T[j-1].unitPrice > T[j].unitPrice ){
                    temp = T[j-1];
                    T[j-1] = T[j];
                    T[j] = temp;
                }
            }
        }
    } else if (!strcmp(args,"STOCK")){
        // trie par stock
        for (int i = N; i > 0; i--){
            for (int j = 1; j < i; j++){
                if ( T[j-1].qtStock > T[j].qtStock){
                    temp = T[j-1];
                    T[j-1] = T[j];
                    T[j] = temp;
                }
            }
        }
    } else if (!strcmp(args,"SEUIL")){
    // trie par stock
        for (int i = N; i > 0; i--){
            for (int j = 1; j < i; j++){
                if ( T[j-1].thresholdAlert > T[j].thresholdAlert){
                    temp = T[j-1];
                    T[j-1] = T[j];
                    T[j] = temp;
                }
            }
        }
    } else if (!strcmp(args,"ENTRE")){
        // trie par seuil
        for (int i = N; i > 0; i--){
            for (int j = 1; j < i; j++){
                if (compareDate(T[j-1].lastEntry, T[j].lastEntry) > 0){
                    temp = T[j-1];
                    T[j-1] = T[j];
                    T[j] = temp;
                }
            }
        }
    } else if (!strcmp(args,"SORTIE")){
        // trie par derniere entree
        for (int i = N; i > 0; i--){
            for (int j = 1; j < i; j++){
                if (compareDate(T[j-1].lastExit, T[j].lastExit) > 0){
                    temp = T[j-1];
                    T[j-1] = T[j];
                    T[j] = temp;
                }
            }
        }

    }

    printHeader();
    for (int i = 0; i < N; i++){
        printProduct(T[i]);
    }



}

void CLI(char* name){
    // on clear la console
    resetCLI(name);

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
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"add")){
            addProductCLI(args, name);
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"edit")){
            editProductCLI(args, name);
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"rm")){
            rmProductClI(args);
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"list")){
            showProductCLI();
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"sr")){
            searchProductCLI(args);
            getchar();
            resetCLI(name);
        }else if (!strcmp(lastCommand,"sort")){
            sortProductCLI(args);
            getchar();
            resetCLI(name);
        } else if (!strcmp(lastCommand,"clr")){
            resetCLI(name);
        }
    } while(strcmp(lastCommand, "exit")); // on quitte le programme quand l'utilisateur entre "exit"

}