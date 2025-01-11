#pragma once

#include <stdio.h>
#include "struct.h"

FILE* initCSV(char* name);
void saveProductToCSV(Product p); // permet de sauvegarder une structure produit
void fetchProductFromCSV(Product* dest); // permet de recup une structure produit
int calcNextID(); // calcule l'id pour le prochain produit