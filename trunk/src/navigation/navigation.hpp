/********************************************************/
/* Application : Fouille de donnees                     */
/* Nom du fichier : navigation.cpp                      */
/* Derniere mise a jour : 23/07/2004                    */
/* Auteur : Noyer Caroline                              */
/********************************************************/


#ifndef __NAVIGATION_HPP__
#define __NAVIGATION_HPP__

#include "../order/table.hpp"
#include "../order/order.hpp"
#include "../ruletree/ruletree.hpp"

// ===========================================================
// Cas d'utilisation = Initialisation de l'arborescence
// => Creation de la premiere arborescence de regles
//
// La table correspondante doit etre disponible
//
// - Calcule l'ordre des sup, l'ordre des inf, les regles triviales
// et les regles generales
// - Sauvegarde les ordres et l'arborescence dans les fichiers XML
//
// en parametre = le nom du fichier XML contenant la table
// ===========================================================
void initArbo(string);


// ===========================================================
void specialiser(string);
void specialiser(string,int,string);


// ===========================================================
void sauter(string);


// ===========================================================
// Wrapper des fonctions precedantes avec des parametres
// compatibles RPC
void initArbo(char*);
void sauter(char*);
void specialiser(char*);


// ===========================================================
void makeRuletreeDTD(string);


#endif // __NAVIGATION_HPP__
