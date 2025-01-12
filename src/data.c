#include "data.h"

FILE* initCSV(char* name, char* access){
    FILE* datacsv = fopen("data.csv",access);
    if (datacsv == NULL){
        printf("[!] Failed to open/create data file when saving product.");
        return NULL;
    }
    return datacsv;
}

void saveProductToCSV(Product p, FILE* datacsv){


    fprintf(datacsv,"%i,%s,%s,%f,%i,%f,%i/%i/%i,%i/%i/%i\n",
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

void fetchProductFromCSV(Product* dest, FILE* datacsv){

    fscanf(datacsv, "%i,%39[^,],%39[^,],%f,%i,%f,%i/%i/%i,%i/%i/%i\n",
           &dest->ID,
           dest->nameP,
           dest->userName,
           &dest->unitPrice,
           &dest->qtStock,
           &dest->thresholdAlert,
           &dest->lastEntry.d, &dest->lastEntry.m, &dest->lastEntry.y,
           &dest->lastExit.d, &dest->lastExit.m, &dest->lastExit.y
           );
}

int calcNextID(){

    FILE* datacsv = initCSV("data.csv","r");
    int counter = 0;
    char c;

    fseek(datacsv, 0, SEEK_SET);
    // on compte le nombre de retour a la ligne vu que chaque produit est sur une ligne
    while (!feof(datacsv)){
        c = fgetc(datacsv);
        if (c == '\n'){
            counter++;
        }
    }

    fclose(datacsv);

    return counter;

}