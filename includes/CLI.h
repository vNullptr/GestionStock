#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "data.h"

#define MAX_INPUT_SIZE 100
#define MAX_ARG_SIZE 90

char* login(); // connection ( demande le nom a l'utilisateur )
void showCommands(); // montre toutes les commande disponible
void addProductCLI(char* args, char* username); // menu pour ajout de produit
void editProductCLI(char* args, char* username); // menu modification produit
void rmProductClI(char* args); // menu suppression produit
void showProductCLI(); // affichage des produits
void searchProductCLI(char* args); // recherche de produit
void sortProductCLI(char* args); // trie de produits
void resetCLI(char* name); // nettoie la console et remet le message de bienvenue
void CLI(char* name); // contient tout le menu qui permet de choisir l'action a executer


// util

int compareDate(Date d1, Date d2); // compare 2 dates
void printHeader(); // affiche le haut du tableau pour affichage du csv
void printProduct(Product p); // affiche les valeurs du csv dans le format d'un tableau