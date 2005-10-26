/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : node.hpp        */
/* Derni�e mise �jour : 23/07/2004      */
/* Auteur : Noyer Caroline        */
/********************************************************/


#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <set> 
#include <algorithm>

#include "../order/setofint.hpp"

using namespace std;

/*
 * Classe Node
 * Classe qui definit un noeud de l'arborescence
 * @author NOYER Caroline
 */

class Node
{
  protected:
    /** Un numero */
    int number;

    /** l'ensemble associe a ce noeud (numeros composant la partie gauche de la regle) */
    SetOfInt itemset;

    /** le ferme�de itemset */
    SetOfInt closure;

    /** le support = nombre de fois que itemset est present dans la table */
    int support;

    /** la confiance de la regle */
    float confidence;

    /** attribut specifiant si la regle est specialisable ou non */
    bool specializable;

    /** attribut specifiant si le noeud a ete traite ou non */
    bool processed;

  public:
    /**
      * Constructeur par defaut d'un element Node
      */
    Node();

    /**
      * Constructeur de recopie
      */
    Node(const Node &);

    /**
      * Desctructeur
      */
    ~Node();

    /**
      * Fonction qui remet l'objet a zero
      */
    void clear();

    /**
      * Surcharge de l'operateur =
      */
    Node& operator=(const Node &);

    /**
      * Surcharge de l'operateur !=
      */
    bool operator!=(Node) const;

    /**
      * Surcharge de l'operateur ==
      */
    bool operator==(Node) const;

    /**
      * Surcharge de l'operateur <
      */
    bool operator<(Node) const;
    
    /**
      * Fonction qui teste si un noeud est nul ou non
      */
    bool isNull() const;

    /**
      * Fonction qui initialise l'attribut number
      * @param un entier correspondant a la nouvelle valeur
      */
    void setNumber(int &) const;
    
    /**
      * Fonction qui recupere l'attribut number
      */
    int getNumber() const;

    /**
      * Fonction qui initialise l'attribut itemset
      * @param un objet de type SetOfInt
      */
    void setSetOfInt(SetOfInt &) const;

    /**
      * Fonction qui recupere l'attribut itemset
      */
    SetOfInt getSetOfInt() const;

    /**
      * Fonction qui initialise l'attribut closure
      * @param un objet de type SetOfInt
      */
    void setClosure(SetOfInt &) const;

    /**
      * Fonction qui recupere l'attribut closure
      */
    SetOfInt getClosure() const;

    /**
      * Fonction qui initialise l'attribut support
      * @param un entier correspondant a la nouvelle valeur
      */
    void setSupport(int &) const;

    /**
      * Fonction qui recupere l'attribut support
      */
    int getSupport() const;

    /**
      * Fonction qui initialise l'attribut confidence
      * @param un reel correspondant a la nouvelle valeur
      */
    void setConfidence(float &) const;

    /**
      * Fonction qui recupere l'attribut confidence
      */
    float getConfidence() const;

    /**
      * Fonction qui initialise l'attribut specializable
      * @param un booleen correspondant a la nouvelle valeur
      */
    void setSpecializable(bool &) const;

    /**
      * Fonction qui recupere l'attribut specializable
      */
    bool getSpecializable() const;

    /**
      * Fonction qui initialise l'attribut processed
      * @param un booleen correspondant a la nouvelle valeur
      */
    void setProcessed(bool &) const;

    /**
      * Fonction qui recupere l'attribut processed
      */
    bool getProcessed() const;

    /**
      * Fonction d'affichage d'un objet de type Node
      */
    void affiche() const;
};


#endif // __NODE_HPP__
