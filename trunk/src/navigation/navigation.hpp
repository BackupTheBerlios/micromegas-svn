/********************************************************/
/* Application : Fouille de donnees			*/
/* Nom du fichier : navigation.hpp			*/
/* Derniere mise a jour : 23/07/2004			*/
/* Auteur : Noyer Caroline				*/
/********************************************************/ 


#ifndef __NAVIGATION_HPP__
#define __NAVIGATION_HPP__

#include "../order/table.hpp"
#include "../order/order.hpp"
#include "../ruletree/ruletree.hpp"

// ===========================================================
// Calcule l'ordre des inf-irreductibles a partir de la table
// dont le nom de fichier est passe en parametre
// Retourne l'ordre ainsi créé
// ===========================================================

Order ordreInf(char *);


// ===========================================================
// Calcule l'ordre des sup-irreductibles a partir de la table
// dont le nom de fichier est passe en parametre
// Retourne l'ordre ainsi créé
// ===========================================================

Order ordreSup(char *);


// ===========================================================
// Cas d'utilisation = Initialisation de l'arborescence
// => Creation de la premiere arborescence de regles
// 
// La table correspondante doit être disponible
//
// - Calcule l'ordre des sup, l'ordre des inf, les regles triviales
// et les regles generales
// - Sauvegarde les ordres et l'arborescence dans les fichiers XML
//
// en parametre = le nom du fichier XML contenant la table
// ===========================================================

void initArbo(char *);


// ===========================================================

void specialiser(char *);


// ===========================================================

void sauter(char *);


// ===========================================================

#endif // __NAVIGATION_HPP__
