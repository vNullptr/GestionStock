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
    strcpy(p.userName, username);
    p.ID = 0; // plus tard je vais utiliser "calcNextID()

    // parsing des arguments
    // on separe les arguments en plusieurs valeur pour remplir la structure
    sscanf(args, "%39[^ ] %f %i %f %i/%i/%i %i/%i/%i",
           p.nameP,
           &p.unitPrice,
           &p.qtStock,
           &p.thresholdAlert,
           &p.lastEntry.d,&p.lastEntry.m,&p.lastEntry.y,
           &p.lastEntry.d,&p.lastEntry.d,&p.lastEntry.y
           );

    // /!\ probleme avec parsing des dates a revoir 

    saveProductToCSV(p);

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
            //editProductCLI();
        } else if (!strcmp(lastCommand,"rm")){
            //rmProductClI();
        } else if (!strcmp(lastCommand,"list")){
            //showProductCLI();
        } else if (!strcmp(lastCommand,"sr")){
            //searchProductCLI();
        }else if (!strcmp(lastCommand,"sort")){
            //sortProductCLI();
        }
    } while(strcmp(lastCommand, "exit")); // on quitte le programme quand l'utilisateur entre "exit"

}