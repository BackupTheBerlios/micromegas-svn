/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : article.hpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Olivier COUPELON        */
/********************************************************/


#ifndef __SETOFINT_HPP__
#define __SETOFINT_HPP__

#include <iostream>
#include <set> 
#include <algorithm>

using namespace std;

/*
 * Classe SETOFINT
 * Classe qui definit la notion d'ensemble d'entiers
 * @author Olivier COUPELON
 */

class SetOfInt : public set<int>
{
  public:
  /**
   * Intersection de deux SetOfInt
   */
    SetOfInt I_intersection(SetOfInt);
  
  /**
   * Union de deux SetOfInt
   */
  SetOfInt I_union(SetOfInt);
    
  /**
   * Différence de deux SetOfInt
   */
  SetOfInt I_minus(SetOfInt);
    
  /**
   * Fonction de test d'inclusion d'un SetOfInt dans un autre
   */
  bool I_includes(SetOfInt);
  
  /**
   * Fonction permettant l'affichage du SetOfInt
   */
  void affiche() const;
};

#endif
