/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : node.cpp        */
/* Derniere mise a jour : 23/07/2004      */
/* Auteur : Noyer Caroline        */
/********************************************************/


#include "node.hpp"


// ==============================================================

Node::Node()
{
  number = 0;
  itemset.clear();
  closure.clear();
  support = 0;
  confidence = 100;
  specializable = false;
  processed = false;
}


// ==============================================================

Node::Node(const Node & init)
{
  number = init.number;
  itemset = init.itemset;
  closure = init.closure;
  support = init.support;
  confidence = init.confidence;
  specializable = init.specializable;
  processed = init.processed;
}


// ==============================================================

Node::~Node()
{
}


// ==============================================================
void Node::clear()
{
  number = -1;
  itemset.clear();
  closure.clear();
  support = 0;
  confidence = 100;
  specializable = false;
  processed = false;
}


// ==============================================================

Node& Node::operator=(const Node & tmp)
{
  this -> number = tmp.number;
  this -> itemset = tmp.itemset;
  this -> closure = tmp.closure;
  this -> support = tmp.support;
  this -> confidence = tmp.confidence;
  this -> specializable = tmp.specializable;
  this -> processed = tmp.processed;

  return (*this);
}


// ==============================================================
/*NE FONCTIONNE PAS
bool Node::operator!=(Node tmp) const
{
  bool test1 = false, test2 = false, test3 = false;

  test1 = (this -> number != tmp.number);
  test2 = (this -> itemset != tmp.itemset);
  test3 = (this -> closure != tmp.closure);
  
  if ((!test1) || (!test2) || (!test3))
    return (true);
  else
    return (false);
}
*/

// ==============================================================

bool Node::operator==(Node tmp) const
{
  bool test1 = false, test2 = false, test3 = false;
  test1 = (this -> number == tmp.number);
  test2 = (this -> itemset == tmp.itemset);
  test3 = (this -> closure == tmp.closure);

  if ((test1) && (test2) && (test3))
    return (true);
  else
    return (false);
}

// ==============================================================
//MARCHE BEAUCOUP MIEUX QUE LA PREMIERE ;)
bool Node::operator!=(Node tmp) const
{
  return(!(*this==tmp));
}

// ==============================================================

bool Node::operator<(Node tmp) const
{
  int tmpNumber = tmp.getNumber();
  if (this -> number < tmpNumber)
    return (true);
  else
    return (false);
}


// ==============================================================

bool Node::isNull() const
{
  SetOfInt tmp;
  if (this -> getNumber() == -1)
  {
    tmp.clear();
    tmp = this -> getSetOfInt();
    if (tmp.empty())
    {
      tmp.clear();
      tmp = this -> getClosure();
      if (tmp.empty())
      {
        return (true);
      }
      else
        return (false);
    }
    else
      return (false);
  }
  else
    return (false);
}


// ==============================================================

void Node::setNumber(int & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> number = init;
}


// ==============================================================

int Node::getNumber() const
{
  return (number);
}


// ==============================================================

void Node::setSetOfInt(SetOfInt & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> itemset = init;
}


// ==============================================================

SetOfInt Node::getSetOfInt() const
{
  return (itemset);
}


// ==============================================================

void Node::setClosure(SetOfInt & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> closure = init;
}


// ==============================================================

SetOfInt Node::getClosure() const
{
  return (closure);
}


// ==============================================================

void Node::setSupport(int & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> support = init;
}


// ==============================================================

int Node::getSupport() const
{
  return (support);
}


// ==============================================================

void Node::setConfidence(float & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> confidence = init;
}


// ==============================================================

float Node::getConfidence() const
{
  return (confidence);
}


// ==============================================================

void Node::setSpecializable(bool & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> specializable = init;
}


// ==============================================================

bool Node::getSpecializable() const
{
  return (specializable);
}


// ==============================================================

void Node::setProcessed(bool & init) const
{
  Node * self = const_cast<Node *>(this);
  self -> processed = init;
}


// ==============================================================

bool Node::getProcessed() const
{
  return (processed);
}


// ==============================================================

void Node::affiche() const
{
  cout << "- - NODE - - - - -  - - - - - - - - - - - -" << endl;
  cout << "- Number : " << number << endl;
  cout << "- SetOfInt : ";
  itemset.affiche();
  cout << "- Closure : ";
  closure.affiche();
  cout << "- Support : " << support << endl;
  cout << "- Confidence : " << confidence << endl;
  cout << "- Specializable : " << specializable << endl;
  cout << "- Processed : " << processed << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
}
