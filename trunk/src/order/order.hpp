/********************************************************/
/* Application : Fouille de donnees                     */
/* Nom du fichier : order.hpp                           */
/* Derniere mise a jour : 23/07/2004                    */
/* Auteur : Noyer Caroline                              */
/********************************************************/


#ifndef __ORDER_HPP__
#define __ORDER_HPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <set>
#include <algorithm>

#include "setofelements.hpp"

using namespace std;

/*
 * Classe Order
 * Classe qui definit un ordre
 * @author NOYER Caroline
 */

class Order
{
  protected:
    /** un ensemble d'elements */
    SetOfElements J;

    /** un vecteur indice par des entiers (number d'un element) correspondant a des elements predecesseurs de l'element indicant l'entree */
    map<int, SetOfElements> imPred;

    /** un vecteur indice par des entiers (number d'un element) correspondant a des elements successeurs de l'element indicant l'entree */
    map<int, SetOfElements> imSucc;

    /** le nom du fichier XML contenant la collection */
    string name;
    
    /** le nom du fichier de la table correspondante */
    string table;

  public:
    /**
      * Constructeur par defaut d'un ordre
      */
    Order();

    /**
      * Constructeur de recopie
      */
    Order(const Order &);

    /**
      * Destructeur
      */
    ~Order();

    /**
      * Fonction qui remet l'ordre a zero
      */
    void clear();

    /**
      * Fonction qui initialise l'attribut J
      * @param un objet de type SetOfElements
      */
    void setJ(SetOfElements);

    /**
      * Fonction qui retourne J
      */
    SetOfElements getJ() const;

    /**
      * Fonction qui initialise l'ensemble des predecesseurs d'un element
      * @param l'element traite
      * @param l'ensemble de ses predecesseurs immediats, un objet de type SetOfElements
      */
    void setImPred(Element, SetOfElements);

    /**
      * Fonction qui recupere l'ensemble des predecesseurs immediats d'un element
      * @param l'element
      */
    SetOfElements getImPred(Element);

    /**
      * Fonction qui initialise l'ensemble des successeurs d'un element
      * @param l'element traite
      * @param l'ensemble de ses successeurs immediats, un objet de type SetOfElements
      */
    void setImSucc(Element, SetOfElements);

    /**
      * Fonction qui recupere l'ensemble des successeurs immediats d'un element
      * @param l'element
      */
    SetOfElements getImSucc(Element);

    /**
      * Fonction qui initialise l'attribut name
      * @param le nom du fichier XML associe a cet ordre
      */
    void setName(string);

    /**
      * Fonction qui recupere le nom du fichier XML associe
      */
    string getName();
    
    /**
      * Fonction qui initialise l'attribut table
      * @param le nom du fichier XML de la table associee a cet ordre
      */
    void setTable(string);
    
    /**
      * Fonction qui recupere le nom du fichier contenant la table associee
      */
    string getTable();

    /**
      * Fonction qui lit l'ordre ï¿½partir du fichier XML
      * @param le nom du fichier XML
      */
    void load();

    /**
      * Fonction qui sauvegarde l'ordre dans le fichier XML
      */
    void save();

    /**
      * Fonction qui retourne J sous la forme d'un ensemble d'entiers
      */
    SetOfInt getJnumbers();

    /**
      * Fonction qui insere un element dans l'ordre
      * @param l'element a inserer dans l'ordre
      */
    void insert(Element);

    /**
      * Fonction qui supprime un element de l'ordre
      * @param l'element a supprimer
      */
    void remove(Element);

    /**
      * Fonction qui renvoie les elements maximaux de l'ordre
      */
    SetOfElements max();

    /**
      * Fonction qui renvoie les elements minimaux de l'ordre
      */
    SetOfElements min();

    /**
      * Fonction qui recopie l'ordre dans un autre
      */
    Order duplicate();

    /**
      * Fonction qui renvoie l'ordre qui correspond ï¿½l'ideal de l'ensemble donne
      * @param un ensemble d'elements
      */
    Order getIdeal(SetOfElements);

    /**
      * Fonction qui enleve le filtre de x de l'ordre
      * @param un element x
      */
    Order removeFilter(Element);

    /**
      * Fonction qui renvoie les successeurs immediats d'un ideal donne dans le treillis des ideaux
      * @param un ensemble d'elements
      */
    SetOfElements imSuccIdeal(SetOfElements);

    /**
      * Fonction qui renvoie les predecesseurs immediats d'un ideal donneï¿½dans le treillis des ideaux
      * @param un ensemble d'elements
      */
    SetOfElements imPredIdeal(SetOfElements);
    
    /**
      * Fonction d'affichage d'un objet de type Order
      */
    void affiche();
    
    /**
      * Fonction de développement
      * Genère un fichier graphviz representant l'ordre
      * @param nom du fichier généré
      * Tranformation en png : dot fichier_généré -Tpng -o image.png
      */
    void genGraph(string);
};


#endif // __ORDER_HPP__
