/********************************************************/
/* Application : Fouille de donnees			*/
/* Nom du fichier : setOfNodes.cpp			*/
/* Derniere mise a jour : 23/07/2004			*/
/* Auteur : Noyer Caroline				*/
/********************************************************/

#include "setofnodes.hpp"

// ==============================================================

SetOfNodes::SetOfNodes()
{
	collection.clear();
}


// ==============================================================

SetOfNodes::SetOfNodes(const SetOfNodes & init)
{
	collection = init.collection;
}


// ==============================================================

SetOfNodes::~SetOfNodes()
{
}


// ==============================================================

void SetOfNodes::clear()
{
	collection.clear();
}


// ==============================================================

SetOfNodes& SetOfNodes::operator=(const SetOfNodes & init)
{
	//collection = tmp.collection;
	SoN_iterator itSet;
	SetOfNodes tmp = init;

	for (itSet = tmp.begin() ; itSet != tmp.end() ; itSet++)
	{
		this -> add(*itSet);
	}

	return (*this);
}


// ==============================================================

/* MIEUX VAUT DEFINIR LE DIFFERENT A PARTIR DU EGAL
bool SetOfNodes::operator!=(SetOfNodes tmp)
{
	bool test1 = false, test2 = false;
	set<Node> set1, set2;
	set1 = this -> getCollection();
	set2 = tmp.getCollection();

	// les collections sont diff�entes si elles n'ont pas le m�e nombre d'��ents
	if (set1.size() != set2.size())
		return (true);

	test1 = includes(set1.begin(), set1.end(), set2.begin(), set2.end());
	test2 = includes(set2.begin(), set2.end(), set1.begin(), set1.end());
	if ((!test1) || (!test2))
		return (true);
	else
		return (false);
}
*/

// ==============================================================

/* PAS TERRIBLE AVEC LES INCLUDE :
bool SetOfNodes::operator==(SetOfNodes tmp)
{
	bool test1 = false, test2 = false;
	set<Node> set1, set2;
	set1 = this -> getCollection();
	set2 = tmp.getCollection();

	test1 = includes(set1.begin(), set1.end(), set2.begin(), set2.end());
	test2 = includes(set2.begin(), set2.end(), set1.begin(), set1.end());
	if ((test1) && (test2))
		return (true);
	else
		return (false);
}
*/

bool SetOfNodes::operator==(SetOfNodes tmp)
{
  set<Node> tmpcollection;
  tmpcollection=tmp.getCollection();
  return(collection==tmpcollection);
}

// ==============================================================

bool SetOfNodes::operator!=(SetOfNodes tmp)
{
  return(!(tmp==*this));
}

// ==============================================================

void SetOfNodes::setCollection(set<Node> init)
{
	collection = init;
}


// ==============================================================

set<Node> SetOfNodes::getCollection() const
{
	return (collection);
}


// ==============================================================

void SetOfNodes::add(Node tmp)
{
	// utilisation de la fonction "insert" de la STL pour les set
	collection.insert(tmp);
}


// ==============================================================

void SetOfNodes::remove(Node tmp)
{
	// on doit supprimer l'element de la collection
	// utilisation de la fonction "erase" de la STL pour les set
	collection.erase(tmp);
}


// ==============================================================

Node SetOfNodes::getNodeBySetOfInt(SetOfInt I)
{
	Node tmpNode;
	SoN_iterator it = begin();

	tmpNode.clear();

	// on parcourt la collection
	while (it != end())
	{
		// si on trouve un noeud ayant le meme itemset que 
		// celui passe en parametre
		if (it -> getSetOfInt() == I)
		{
			// alors on retourne le noeud
			return (*it);
		}
		it++;
	}

	// rien n'a ete trouve => on renvoie un noeud vide
	return (tmpNode);
}


// ==============================================================

Node SetOfNodes::getNodeByNumber(int num)
{
	Node tmpNode;
	SoN_iterator it = begin();

	tmpNode.clear();

	// on parcourt la collection
	while (it != end())
	{
		// si on trouve un noeud ayant pour numero num
		if (it -> getNumber() == num)
		{
			// alor on retourne ce noeud
			return (*it);
		}
		it++;
	}

	// rien n'a ete trouve => on renvoie un noeud vide
	return (tmpNode);
}

// ==============================================================

SetOfInt SetOfNodes::getSetOfIntByNumber(int num)
{
	SetOfInt tmpSetOfInt;
	SoN_iterator it = begin();
	
	tmpSetOfInt.clear();
	
	// on parcourt la collection
	while (it != end())
	{
		// si on trouve un noeud ayant pour numero num
		if (it -> getNumber() == num)
		{
			// on retoune l'itemset de ce noeud
			return (it -> getSetOfInt());
		}
		it++;
	}
	
	// si rien n'a ete trouve on renvoie un SetOfInt vide
	return (tmpSetOfInt);
}


// ==============================================================

void SetOfNodes::updateClosureAll(SetOfInt T)
{
	SoN_iterator it;
	bool test;
	int tmpSupport = 0;
	SetOfInt tmpSetOfInt, tmpInter;
	
	// pour chaque noeud de la collection
	for (it = begin() ; it != end() ; it++)
	{
		tmpSetOfInt.clear();
		tmpSetOfInt = it -> getSetOfInt();
		test = false;
		test = includes(T.begin(), T.end(), tmpSetOfInt.begin(), tmpSetOfInt.end());
		if (test)
		{
			// N.setClosure(N.getClosure() INTER T)
			tmpSetOfInt.clear();
			tmpInter.clear();
			tmpSetOfInt = it -> getClosure();
			tmpInter = tmpSetOfInt.I_intersection(T);
			it -> setClosure(tmpInter);

			// N.setSupport(N.getSupport() + 1)
			tmpSupport = it -> getSupport() + 1;
			it -> setSupport(tmpSupport);
		}
	}
}


// ==============================================================
/*
void SetOfNodes::closureAll(char * filename)
{
	Table tmpTable;
	SetOfInt tmpSetOfInt, tmpTuple;
	SoN_iterator it;
	int nbTuples;
	int tmpSupport = 0;

	tmpTable.rewind(filename); // utilise la fonction readHeader()
	
	for (it = begin() ; it != end() ; it++)
	{
		tmpSetOfInt.clear();
		tmpSetOfInt = tmpTable.getListItems();
		it -> setClosure(tmpSetOfInt);

		it -> setSupport(tmpSupport);
	}

	// pour chaque tuple on met �jour le ferm�	nbTuples = tmpTable.getNbTuples();
	for (int i = 0 ; i < nbTuples ; i++)
	{
		tmpTuple.clear();
		tmpTuple = tmpTable.readTuple();
		updateClosureAll(tmpTuple);
	}
}
*/

// ==============================================================

void SetOfNodes::affiche()
{
	// utilise la fonction affiche() du TDA Element
	SoN_iterator itSet;

	for (itSet = begin() ; itSet != end() ; itSet++)
	{
		itSet -> affiche();
		cout << endl;
	}
}

