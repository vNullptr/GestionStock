#include "data.h"

FILE* initCSV(char* name){
    FILE* datacsv = fopen("data.csv","a+");
    if (datacsv == NULL){
        printf("[!] Failed to open/create data file when saving product.");
        return NULL;
    }
    return datacsv;
}

void saveProductToCSV(Product p){

    FILE* datacsv = initCSV("data.csv");

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

    fclose(datacsv);


}

void fetchProductFromCSV(Product* dest){

    FILE* datacsv = initCSV("data.csv");

    fseek(datacsv, 0, SEEK_SET);

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