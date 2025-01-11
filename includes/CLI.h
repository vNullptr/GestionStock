#pragma once

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "data.h"

#define MAX_INPUT_SIZE 100
#define MAX_ARG_SIZE 90

char* login(); // connection ( demande le nom a l'utilisateur )
void showCommands(); // montre toutes les commande disponible
void addProductCLI(char* args, char* username); // menu pour ajout de produit
void editProductCLI(); // menu modification produit
void rmProductClI(); // menu suppression produit
void showProductCLI(); // affichage des produits
void searchProductCLI(); // recherche de produit
void sortProductCLI(); // trie de produits
void CLI(char* name); // contient tout le menu qui permet de choisir l'action a executer