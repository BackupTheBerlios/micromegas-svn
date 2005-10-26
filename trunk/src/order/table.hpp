/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : table.hpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#ifndef __TABLE_HPP__
#define __TABLE_HPP__


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#include <libxml/xmlreader.h>

#include <map>
#include <algorithm>

#include "setofint.hpp"

using namespace std;


/*
 * Classe Table
 * Classe qui definit le TDA Table avec la gestion des fichiers XML
 * @author NOYER Caroline, Olivier COUPELON
 */

class Table
{
  protected:
    /** nom du fichier XML contenant la table */
    string name;

    /** nombre de tuples dans la table */
    int nbTuples;

    /** nombre d'items dans la table */
    int nbItems;

    /** tableau de correspondance */
    map<string,int> mapping;

    /** pointeur dans le fichier XML pour la lecture */
    xmlTextReaderPtr xmlReader;

    /** numero du tuple courant */
    int currentTuple;

  public:
    /**
      * Constructeur par defaut d'une table
      */
    Table();

    /**
      * Constructeur de recopie
      */
    Table(const Table &);

    /**
      * Destructeur
      */
    ~Table();

    /**
      * Fonction qui remet la table a zero
      */
    void clear();

    /**
      * Fonction qui initialise l'attribut name
      * @param le nom du fichier XML correspondant
      */
    //void setName(char *);
    void setName(string);

    /**
      * Fonction qui retourne le nom du fichier contenant la table
      */
    //char * getName() const;
    string getName() const;

    /**
      * Fonction qui initialise l'attribut nbTuple
      * @param un entier correspondant au nombre de tuples dans la table
      */
    void setNbTuples(int);

    /**
      * Fonction qui retourne le nombre de tuples de la table
      */
    int getNbTuples() const;

    /**
      * Fonction qui initialise l'attribut nbItems
      * @param un entier correspondant au nombre d'items dans la table
      */
    void setNbItems(int);

    /**
      * Fonction qui retourne le nombre d'items de la table
      */
    int getNbItems() const;
    
    /**
      * Fonction qui initialise l'attribut mapping
      * @param un objet de type map
      */
    //void setMapping(map<char *,int>);
    void setMapping(map<string,int>);

    /** 
      * Fonction qui recupere le mapping de la table
      */
    //map<char *,int> getMapping() const;
    map<string,int> getMapping() const;

    /**
      * Fonction qui initialise le pointeur du fichier XML
      * @param un objet de type xmlTextReaderPtr
      */
    void setXmlReader(xmlTextReaderPtr);

    /**
      * Fonction qui retourne le pointeur du fichier XML
      */
    xmlTextReaderPtr getXmlReader() const;

    /**
      * Fonction qui initialise l'attribut currentTuple
      * @param un entier correspondant au numero du tuple courant
      */
    void setCurrentTuple(int);

    /**
      * Fonction qui recupere le numero du tuple courant
      */
    int getCurrentTuple() const;

    /**
      * Fonction qui ouvre le fichier et place sur le premier tuple
      * @param le nom du fichier XML
      */
    bool rewind();

    /**
      * Fonction qui lit l'en-tete du fichier XML
      */
    void readHeader();

    /**
      * Fonctions de traitement pour la fonction initCorrespond
      * @param l'etat courant (cf automate)
      * @param un compteur
      */
    void ICTraiteDebut(int &, int &);
    void ICTraiteListItems(int &, int &);
    void ICTraiteItem(int &, int &);
    
    /**
      * Fonction qui initialise le tableau des correspondances
      */
    void initCorrespond();

    /**
      * Fonctions de traitement pour la fonction readTuple
      * @param l'etat courant (cf automate)
      * @param un objet de type SetOfInt correspondant au tuple lu
      */
    void RTTraiteDebut(int &, SetOfInt &);
    void RTTraiteTuple(int &, SetOfInt &);
    void RTTraiteItem(int &, SetOfInt &);
    
    /**
      * Fonction qui lit UN tuple dans le fichier
      */
    SetOfInt readTuple();

    /**
      * Fonction qui ecrit l'en-tete du fichier XML
      */
    void writeHeader();

    /**
      * Fonction qui ecrit un tuple
      * @param un objet de type SetOfInt representant le tuple
      */
    void writeTuple(SetOfInt);

    /**
      * Fonction qui ecrit la fin du fichier XML
      */
    void writeEnd();

    /**
      * Fonction qui retourne un SetOfInt contenant tous les items
      */
    SetOfInt getListItems();

    /**
      * Fonction qui recupere l'item par son nom
      * @param le nom de l'item
      */
    int getItemByName(string);

    /**
      * Fonction qui initialise le nom de l'item par rapport a son numero
      * @param le numero de l'item
      * @param le nom a lui associer
      */
    void setItemName(int, string);

    /**
      * Fonction qui recupere le nom de l'item par le numero associe
      * @param le numero de l'item
      */
    string getNameOfItem(int);

    /**
      * Fonction d'affichage pour verifier les test
      */
    void affiche();
    
    /**
      * Fonction permettant d'afficher le mapping (implementee par la suite)
      */
      
    void affMapping();
};


#endif // __TABLE_HPP__
