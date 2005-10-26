/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : element.cpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#include "element.hpp"


// ==============================================================

Element::Element()
{
  number = 0;
  SetOfInt itemSet;
}


// ==============================================================

Element::Element(const Element & init)
{
  number = init.number;
  itemSet = init.itemSet;
}


// ==============================================================

Element::~Element()
{

}


// ==============================================================

void Element::clear()
{
  number = 0;
  itemSet.clear();
}


// ==============================================================

Element& Element::operator=(const Element & tmp)
{
  if (this != &tmp)
  {
    this -> number = tmp.number;
    this -> itemSet = tmp.itemSet;
  }
  return (*this);
}


// ==============================================================

bool Element::operator!=(Element tmp) const
{
  if ((this -> number != tmp.getNumber()) || (this -> itemSet != tmp.getItemSet()))
    return (true);
  else
    return (false);
}

// ==============================================================

bool Element::operator==(Element tmp) const
{
  if ((this -> number == tmp.getNumber()) && (this -> itemSet == tmp.getItemSet()))
    return (true);
  else
    return (false);
}


// ==============================================================

bool Element::operator<(Element tmp) const
{
  int tmpNumber = tmp.getNumber();
  if (this -> number < tmpNumber)
    return (true);
  else
    return (false);
}


// ==============================================================

void Element::setNumber(int initNumber)
{
  number = initNumber;
}


// ==============================================================

int Element::getNumber() const
{
  return (number);
}


// ==============================================================

void Element::setItemSet(SetOfInt & initItemSet) const
{
  Element * self = const_cast<Element *>(this);
  self -> itemSet = initItemSet;
}


// ==============================================================

SetOfInt Element::getItemSet() const
{
  return (itemSet);
}


// ==============================================================

void Element::affiche() const
{
  cout << number << " = ";
  itemSet.affiche();
}
