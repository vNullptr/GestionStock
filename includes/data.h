#pragma once

#include <stdio.h>
#include "struct.h"

FILE* initCSV(char* name, char* access);
void saveProductToCSV(Product p, FILE* datacsv); // permet de sauvegarder une structure produit
void fetchProductFromCSV(Product* dest, FILE* datacsv); // permet de recup une structure produit
int calcNextID(); // calcule l'id pour le prochain produit