#pragma once


// tableau contenant toute les commandes
static char commands[][2][250] = {
        {"add [Nom Produit] [Prix Unitaire] [Quantite Stock] [Seuille d'alerte] [Derneire entree :d/m/y] [Derniere sortie :d/m/y] ","add a product."},
        {"edit [ID]","Modifie les propriete du produit."},
        {"rm [ID Produit]", "Supprime le produit de la liste."},
        {"sr [TYPE:ID/NOM] [ID/NOM]","Chercher un ou plusieurs produit selon leur ID ou leur nom."},
        {"list","affiche tout le stock."},
        {"sort [TYPE:PRIX/STOCK/SEUIL/ENTRE/SORTIE]", "trie en fonction du choix de l'utilisateur et affiche le stock."}

};