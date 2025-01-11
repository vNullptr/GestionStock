#pragma once

typedef struct {
    int d;
    int m;
    int y;
} Date;

typedef struct {
    int ID;
    char nameP[40]; // nom produit
    char userName[40];
    float unitPrice;
    int qtStock;
    float thresholdAlert; // seuil d'alerte
    Date lastEntry; // derniere entre
    Date lastExit; // derniere sortie
} Product;