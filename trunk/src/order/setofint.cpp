/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : article.hpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Olivier COUPELON        */
/********************************************************/


#include "setofint.hpp"

// ==============================================================

SetOfInt SetOfInt::I_intersection(SetOfInt tmp)
{
  SetOfInt out;
  insert_iterator<SetOfInt> ii (out, out.begin());
  set_intersection(this->begin(), this->end(), tmp.begin(), tmp.end(), ii);
  return (out);
}


// ==============================================================

SetOfInt SetOfInt::I_union(SetOfInt tmp)
{
  SetOfInt out;
  insert_iterator<SetOfInt> ii (out, out.begin());
  set_union(this->begin(), this->end(), tmp.begin(), tmp.end(), ii);
  return (out);
}


// ==============================================================

SetOfInt SetOfInt::I_minus(SetOfInt tmp)
{
  SetOfInt out;
  insert_iterator<SetOfInt> ii (out, out.begin());
  set_difference(this->begin(), this->end(), tmp.begin(), tmp.end(), ii);
  return (out);
}


// ==============================================================

bool SetOfInt::I_includes(SetOfInt tmp)
{
  if (includes(this->begin(), this->end(), tmp.begin(), tmp.end()))
    return (true);
  else
    return (false);
}


// ==============================================================

void SetOfInt::affiche() const
{
  cout << "(" ;
  for (SetOfInt::iterator it = this->begin() ; it != this->end() ; it++)
  {
    cout << " - " << *it << " - ";
  }
  cout << ")" ;
  cout << endl;
}
