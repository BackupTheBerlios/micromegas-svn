/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : element.hpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#ifndef __ELEMENT_HPP__
#define __ELEMENT_HPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <set> 
#include <algorithm>

#include "setofint.hpp"

using namespace std;

/*
 * Classe Element
 * Classe qui definit un element de l'ordre
 * @author NOYER Caroline
 */

class Element
{
  protected:
    /** Un numero (l'item s'il s'agit d'un sup-irreductible) */
      int number;

    /** l'ensemble associé à l'element */
    SetOfInt itemSet;

  public:
    /**
      * Constructeur par defaut d'un element
      */
    Element();

    /**
      * Constructeur de recopie
      */
    Element(const Element &);

    /**
      * Desctructeur
      */
    ~Element();

    /**
      * Fonction qui remet l'element a zero
      */
    void clear();

    /**
      * Surcharge de l'operateur =
      */
    Element& operator=(const Element &);

    /**
      * Surcharge de l'operateur !=
      */
    bool operator!=(Element) const;

    /**
      * Surcharge de l'operateur !=
      */
    bool operator==(Element) const;

    /**
      * Surcharge de l'operateur <
      */
    bool operator<(Element) const;

    /**
      * Fonction qui initialise l'attribut number
      * @param l'entier avec lequel on initialise
      */
    void setNumber(int);

    /**
      * Fonction qui recupere la valeur de l'attribut number
      */
    int getNumber() const;

    /**
      * Fonction qui initialise l'attribut itemSet
      * @param l'ensemble a initialiser
      */
    void setItemSet(SetOfInt &) const;

    /**
      * Fonction qui recupere l'ensemble itemSet
      */
    SetOfInt getItemSet() const;

    /**
      * Fonction d'affichage d'un objet de type Element
      */
    void affiche() const;
};


#endif // __ELEMENT_HPP__
