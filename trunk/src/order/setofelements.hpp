/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : setOfElements.hpp      */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#ifndef __SETOFELEMENTS_HPP__
#define __SETOFELEMENTS_HPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#include <libxml/xmlreader.h>

#include <map>
#include <algorithm>
#include <map>

#include "table.hpp"
#include "element.hpp"

using namespace std;

/*
 * Classe SetOfElements
 * Classe qui definit un ensemble d'elements
 * @author NOYER Caroline
 */

class SetOfElements
{
  protected:
    /** un ensemble d'elements */
    set<Element> collection;

    /** le nom du fichier XML contenant la collection */
    string name;

    /** le nom du fichier XML contenant la table correspondante */
    string table;

  public:
    /**
      * Constructeur par defaut d'un setOfElements
      */
    SetOfElements();

    /**
      * Constructeur de recopie
      */
    SetOfElements(const SetOfElements &);

    /**
      * Calcule l'ensemble des Sup-irreductibles
      * Attention, ils sont calculés à l'aide de la
      * table, et ne sont donc pas nécessairement les
      * mêmes que ceux voulus.
      * @param Le nom de la table
      */
    void setSup(const string &);
  
    /**
      * Calcule l'ensemble des Inf-irreductibles
      * @param Le nom de la table
      */
    void setInf(const string &);
  
    /**
      * Destructeur
      */
    ~SetOfElements();

    /**
      * Fonction qui efface les elements de la collection
      */
    void clear();

    /**
      * Surcharge de l'operateur =
      */
    SetOfElements & operator=(const SetOfElements &);

    /**
      * Surcharge de l'operateur !=
      */
    bool operator!=(SetOfElements);

    /**
      * Surcharge de l'operateur ==
      */
    bool operator==(SetOfElements);

    /**
      * Fonction qui initialise l'attribut collection
      * @param l'ensemble d'elements constituant la collection
      */
    void setCollection(set<Element>);

    /**
      * Fonction qui recupere la collection
      */
    set<Element> getCollection() const;

    /**
      * Fonction qui recupere le nombre d'elements de la collection
      */
    int getNbElements() const;

    /**
      * Fonction qui initialise l'attribut name
      * @param le nom du fichier contenant la collection
      */
    //void setName(char *);
    void setName(string);

    /**
      * Fonction qui retourne le nom du fichier XML contenant la collection
      */
    string getName() const;

    /**
      * Fonction qui initialise l'attribut tableName
      * @param le nom du fichier XML contenant la table
      */
    void setTable(string);

    /**
      * Fonction qui retourne le nom du fichier XML de la table correspondante
      */
    string getTable() const;
    
    /**
      * Fonction qui effectue l'union de deux objets SetOfElements
      * en prenant en compte les elementSet plutot que les number des elements
      */
    SetOfElements unionSets(SetOfElements);

    /**
      * Fonction qui effectue l'union entre deux objets SetOfElements
      */
    SetOfElements SoE_union(SetOfElements);

    /**
      * Fonction qui effectue la difference entre deux objets SetOfElements
      */
    SetOfElements SoE_minus(SetOfElements);

    /**
      * Fonction de traitements pour l'automate
      * @param l'etat actuel de l'automate (qui sera eventuellement modifie)
      * @param le reader XML (qui sera lui aussi modifie)
      * @param un booleen qui teste si un number est bien present pour former l'element
      * @param un booleen qui teste si un set est bien present pour former un element
      * @param l'element courant
      * @param la table associee a cette collection
      */
    void SoETraiteDebut(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);
    void SoETraiteCollection(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);
    void SoETraiteElement(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);
    void SoETraiteNumber(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);
    void SoETraiteSet(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);
    void SoETraiteItem(int &, xmlTextReaderPtr &, bool &, bool &, Element &, Table &);

    /**
      * Fonction qui lit la collection ï¿½partir du fichier XML
      */
    void load();

    /**
      * Fonction qui sauvegarde la collection dans le fichier XML
      */
    void save();

    /**
      * Fonction qui ajoute un element a la collection
      * @param un objet de type Element
      */
    void add(Element);

    /**
      * Fonction qui supprime un element de la collection
      * @param l'element a supprimer
      */
    void remove(Element);

    /**
      * Fonction qui recupere le numero d'un element par son ensemble associe    
      * @param l'objet de type SetOfInt
      */
    int getNumberBySet(SetOfInt);

    /**
      * Fonction qui recupere l'ensemble associe a un element par son numero
      * @param le numero correspondant a cet element
      */
    SetOfInt getSetByNumber(int);

    /**
      * Fonction qui renvoie un ensemble d'entiers correspondant a la liste des number des elements
      */
    SetOfInt getNumbers();
    
    /** 
      * Cette fonction renvoie le prochain numéro d'élément non encore utilisé dans ce SetOfElements
      */
    int getNextAvailableNumber();

    /**
      * Fonction qui retourne le nombre d'elements de l'ensemble
      */
    int getSize();

    /**
      * Fonction qui calcule la fermeture de tous les itemsets des elements
      * @param le nom de la table correspondante
      */
    void closureAll(string);

    /**
      * Definition d'un iterateur sur le TDA SetOfElements
      */
    // en fait il suffit de definir l'iterateur sur la collection, de type set<Element>
    typedef set<Element>::iterator SoE_iterator;
    SoE_iterator begin() {return collection.begin();}
    SoE_iterator end() {return collection.end();}

    /**
      * Fonction d'affichage d'un objet de type SetOfElements
      */
    void affiche(); 
};


#endif // __SETOFELEMENTS_HPP__
