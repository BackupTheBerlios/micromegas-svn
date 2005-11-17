/********************************************************/
/* Application : Fouille de donnees                     */
/* Nom du fichier : ruletree.cpp                        */
/* Derniere mise a jour : 23/07/2004                    */
/* Auteur : Noyer Caroline                              */
/********************************************************/


#include "ruletree.hpp"

// constantes utilisees pour les automates
#define baliseRuleTree "RuleTree"
#define baliseRule "Rule"
#define balisePrincipalItem "PrincipalItem"
#define baliseLeftSide "LeftSide"
#define baliseRightSide "RightSide"
#define baliseItem "Item"

#define baliseOuvrante 1
#define contenuBalise 3
#define baliseFermante 15

#define ADebut 0
#define ARuleTree 1
#define ARule 2
#define ALeftSide 3
#define ALSItem 4
#define APrincipalItem 5
#define ARightSide 6
#define ARSItem 7
#define AFin 8

// constantes pour le traitement de chaine
#define nameItem '~'
#define implique '#'


// ==============================================================

RuleTree::RuleTree()
{
	listNodesItem.clear();
	listNodes.clear();
	parent.clear();
	children.clear();
	name = "";
	table = "";
	orderSup.clear();
	orderInf.clear();
	setLastNumber(0);
}


// ==============================================================

RuleTree::RuleTree(const RuleTree & init)
{
	listNodesItem = init.listNodesItem;
	listNodes = init.listNodes;
	parent = init.parent;
	children = init.children;
	name = init.name;
	table = init.table;
	orderSup = init.orderSup;
	orderInf = init.orderInf;
	setLastNumber(init.getLastNumber());
}


// ==============================================================

RuleTree::~RuleTree()
{}


// ==============================================================

void RuleTree::clear()
{
	listNodesItem.clear();
	listNodes.clear();
	parent.clear();
	children.clear();
	name = "";
	table = "";
	orderSup.clear();
	orderInf.clear();
	setLastNumber(0);
}


// ==============================================================

void RuleTree::setListNodesItem(map<Node, int> init)
{
	listNodesItem.clear();
	listNodesItem = init;
}


// ==============================================================

map<Node, int> RuleTree::getListNodesItem() const
{
	return (listNodesItem);
}


// ==============================================================

void RuleTree::setListNodes(SetOfNodes init)
{
	listNodes.clear();
	listNodes = init;
}


// ==============================================================

SetOfNodes RuleTree::getListNodes() const
{
	return (listNodes);
}


// ==============================================================

void RuleTree::setParent(Node N, Node pere)
{
	int num;
	num = N.getNumber();
	parent[num].clear();
	parent[num] = pere;
}


// ==============================================================

Node RuleTree::getParent(Node N)
{
	Node tmpNode;
	int num;
	map<int,Node>::iterator itParent;
	num = N.getNumber();
	tmpNode.clear();

	for (itParent = parent.begin() ; itParent != parent.end() ; itParent++)
	{
		if (itParent -> first == num)
			return (itParent -> second);
	}

	return (tmpNode);
}


// ==============================================================

void RuleTree::setChildren(Node N, SetOfInt init)
{
	int num;
	num = N.getNumber();
	children[num].clear();
	children[num] = init;
}


// ==============================================================

SetOfInt RuleTree::getChildren(Node N)
{
	SetOfInt tmpSetOfInt;
	int num;
	map<int,SetOfInt>::iterator itChildren;
	num = N.getNumber();
	tmpSetOfInt.clear();

	for (itChildren = children.begin() ; itChildren != children.end() ; itChildren++)
	{
		if (itChildren -> first == num)
			return (itChildren -> second);
	}

	return (tmpSetOfInt);
}


// ==============================================================

void RuleTree::setName(string init)
{
	name = init;
}


// ==============================================================

string RuleTree::getName() const
{
	return (name);
}


// ==============================================================

void RuleTree::setTable(string init)
{
	table = init;
}


// ==============================================================

string RuleTree::getTable() const
{
	return (table);
}


// ==============================================================

void RuleTree::setOrderSup(Order init)
{
	orderSup = init.duplicate();
}


// ==============================================================

Order RuleTree::getOrderSup() const
{
	return (orderSup);
}


// ==============================================================

void RuleTree::setOrderInf(Order init)
{
	orderInf = init;
}


// ==============================================================

Order RuleTree::getOrderInf() const
{
	return (orderInf);
}


// ==============================================================

void RuleTree::setLastNumber(int init)
{
	lastNumber = init;
}


// ==============================================================

int RuleTree::getLastNumber() const
{
	return (lastNumber);
}


// ==============================================================

void RuleTree::setListItems(SetOfInt init)
{
	listItems = init;
}


// ==============================================================

SetOfInt RuleTree::getListItems() const
{
	return (listItems);
}


// ==============================================================

void RuleTree::setNodeItem(Node N, int item)
{
	listNodesItem[N] = item;
}


// ==============================================================

int RuleTree::getItemByNode(Node N)
{
	map<Node, int>::iterator itMap;

	// pour chaque element de listNodesItem
	for (itMap = listNodesItem.begin() ; itMap != listNodesItem.end() ; itMap++)
	{
		// si le numero correspond au number du noeud passe en parametre
		if ((itMap -> first).getNumber() == N.getNumber())
			// alors on retourne l'item
			return (itMap -> second);
	}

	// sinon on retourne -1 par defaut
	return (-1);
}


// ==============================================================

Node RuleTree::getNodeByNumber(int num)
{
	Node tmp;
	set<Node> tmpColl;
	set<Node>::iterator it;

	tmp.clear();
	tmpColl = listNodes.getCollection();

	// pour chaque noeud de listNodes
	for (it = tmpColl.begin() ; it != tmpColl.end() ; it++)
	{
		// si le numero du noeud est le meme que num
		if (it -> getNumber() == num)
			// alors on retourne ce noeud
			return (*it);
	}

	// rien n'a ete trouve => on renvoie un noeud nul
	return (tmp);
}


// ==============================================================

SetOfInt RuleTree::getNodesNumbers()
{
	SetOfInt tmpNumbers;
	tmpNumbers.clear();
	set<Node> tmpSetOfNodes;
	set<Node>::iterator itSoN;

	tmpNumbers.clear();
	tmpSetOfNodes = listNodes.getCollection();

	// pour chaque noeud de listNodes
	for (itSoN = tmpSetOfNodes.begin() ; itSoN != tmpSetOfNodes.end() ; itSoN++)
	{
		// on insere le numero du noeud courant dans un ensemble
		tmpNumbers.insert(itSoN -> getNumber());
	}

	// on retourne l'ensemble obtenu
	return (tmpNumbers);
}


// ==============================================================

SetOfElements RuleTree::itemsetToSetOfElements(SetOfInt I)
{
	set<int> tmp = I;
	set<int>::iterator it;
	Element tmpElement;
	SetOfElements tmpSetOfElements;
	SetOfInt tmpSetOfInt;

	tmpSetOfElements.clear();
	// pour chaque element de I
	for (it = tmp.begin() ; it != tmp.end() ; it++)
	{
		// on récupere l'itemset correspondant au numero du noeud
		// et on forme un element
		tmpElement.clear();
		tmpElement.setNumber(*it);
		tmpSetOfInt = listNodes.getSetOfIntByNumber(*it);
		tmpElement.setItemSet(tmpSetOfInt);
		tmpSetOfElements.add(tmpElement);
	}
	return (tmpSetOfElements);
}


// ==============================================================

SetOfNodes RuleTree::itemsetToSetOfNodes(SetOfInt I)
{
	set<int> tmp = I;
	set<int>::iterator it;
	Node tmpNode;
	SetOfNodes tmpSetOfNodes;

	tmpSetOfNodes.clear();
	// pour chaque element de I
	for (it = tmp.begin() ; it != tmp.end() ; it++)
	{
		// on récupère le noeud correspondant a ce numero
		tmpNode.clear();
		tmpNode = listNodes.getNodeByNumber(*it);
		// et on l'insere dans le SetOfNodes
		tmpSetOfNodes.add(tmpNode);
	}

	return (tmpSetOfNodes);
}


// ==============================================================

void RuleTree::ATraiteDebut(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table & tmpTable)
{
	// Si <RuleTree>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("RuleTree")) == 0))
	{
		// le nom du fichier XML_A
		xmlChar * attrTable = xmlCharStrdup("table");
		table = (char *)(xmlTextReaderGetAttribute(reader, attrTable));
		setTable(table);

		tmpTable.setName(table);
		tmpTable.rewind();

		listItems = tmpTable.getListItems();

		// nom du fichier XML_ORDER pour supOrder
		xmlChar * attrSupOrder = xmlCharStrdup("supOrder");
		char * tmpSupOrder = NULL;
		tmpSupOrder = (char *)(xmlTextReaderGetAttribute(reader, attrSupOrder));
		orderSup.clear();
		orderSup.setName(tmpSupOrder);
		orderSup.setTable(table);
		orderSup.load();

		// nom du fichier XML_ORDER pour infOrder
		xmlChar * attrInfOrder = xmlCharStrdup("infOrder");
		char * tmpInfOrder = NULL;
		tmpInfOrder = (char *)(xmlTextReaderGetAttribute(reader, attrInfOrder));
		orderInf.clear();
		orderInf.setName(tmpInfOrder);
		orderInf.setTable(table);
		orderInf.load();

		int numero = 0;
		setLastNumber(numero);

		etat = ARuleTree;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteRuleTree(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	// Si <Rule>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Rule")) == 0))
	{
		Node tmpNode;
		int tmpInt;
		float tmpFloat;
		bool tmpBool;
		int numero = getLastNumber();

		// initialisation d'un objet de type Node
		tmpNode.setNumber(numero);
		numero++;
		setLastNumber(numero);

		// on récupère les attributs de <Rule ...>
		// support de la règle
		xmlChar * attrSupport = xmlCharStrdup("support");
		char * tmpSupport = "";
		tmpSupport = (char *)(xmlTextReaderGetAttribute(reader, attrSupport));
		tmpInt = atoi(tmpSupport);
		tmpNode.setSupport(tmpInt);

		// confiance de la règle
		xmlChar * attrConfidence = xmlCharStrdup("confidence");
		char * tmpConfidence = "";
		tmpConfidence = (char *)(xmlTextReaderGetAttribute(reader, attrConfidence));
		tmpFloat = (float)(atoi(tmpConfidence));
		tmpNode.setConfidence(tmpFloat);

		// specialisation de la règle
		xmlChar * attrSpecializable = xmlCharStrdup("specializable");
		char * tmpSpecializable = "";
		tmpSpecializable = (char *)(xmlTextReaderGetAttribute(reader, attrSpecializable));
		if (strcmp(tmpSpecializable, "yes") == 0)
			tmpBool = true;
		else
			// sinon dans tous les cas c'est faux
			// (par défaut on considèrera qu'une règle n'est pas spécialisable)
			tmpBool = false;
		tmpNode.setSpecializable(tmpBool);

		// traitement du noeud
		xmlChar * attrProcessed = xmlCharStrdup("processed");
		char * tmpProcessed = "";
		tmpProcessed = (char *)(xmlTextReaderGetAttribute(reader, attrProcessed));
		if (strcmp(tmpProcessed, "yes") == 0)
			tmpBool = true;
		else
			// sinon dans tous les cas c'est faux
			// (par défaut on considèrera qu'un noeud n'est pas traité)
			tmpBool = false;
		tmpNode.setProcessed(tmpBool);

		// on empile le noeud ainsi initialisé
		pile.push(tmpNode);

		// initialisation du niveau
		niveau = 0;

		etat = ARule;
	}

	// Si </RuleTree>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("RuleTree")) == 0))
	{
		// on est Ã  la fin du fichier XML
		etat = AFin;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteRule(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	// Si <LeftSide>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("LeftSide")) == 0))
	{
		ensItems.clear();
		etat = ALeftSide;
	}

	// Si <PrincipalItem>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("PrincipalItem")) == 0))
	{
		nomItem = "";
		etat = APrincipalItem;
	}

	// Si <RightSide>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("RightSide")) == 0))
	{
		ensItems.clear();
		etat = ARightSide;
	}

	// Si <Rule>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Rule")) == 0))
	{
		Node tmpNode;
		int tmpInt;
		float tmpFloat;
		bool tmpBool;
		int numero = getLastNumber();

		// initialisation d'un objet de type Node
		tmpNode.setNumber(numero);

		// on récupère les attributs de <Rule ...>
		// support de la règle
		xmlChar * attrSupport = xmlCharStrdup("support");
		char * tmpSupport = "";
		tmpSupport = (char *)(xmlTextReaderGetAttribute(reader, attrSupport));
		tmpInt = atoi(tmpSupport);
		tmpNode.setSupport(tmpInt);

		// confiance de la règle
		xmlChar * attrConfidence = xmlCharStrdup("confidence");
		char * tmpConfidence = "";
		tmpConfidence = (char *)(xmlTextReaderGetAttribute(reader, attrConfidence));
		tmpFloat = (float)(atoi(tmpConfidence));
		tmpNode.setConfidence(tmpFloat);

		// specialisation de la règle
		xmlChar * attrSpecializable = xmlCharStrdup("specializable");
		char * tmpSpecializable = "";
		tmpSpecializable = (char *)(xmlTextReaderGetAttribute(reader, attrSpecializable));
		if (strcmp(tmpSpecializable, "yes") == 0)
			tmpBool = true;
		else
			// sinon dans tous les cas c'est faux
			// (par défaut on considèrera qu'une règle n'est pas spécialisable)
			tmpBool = false;
		tmpNode.setSpecializable(tmpBool);

		// traitement du noeud
		xmlChar * attrProcessed = xmlCharStrdup("processed");
		char * tmpProcessed = "";
		tmpProcessed = (char *)(xmlTextReaderGetAttribute(reader, attrProcessed));
		if (strcmp(tmpProcessed, "yes") == 0)
			tmpBool = true;
		else
			// sinon dans tous les cas c'est faux
			// (par défaut on considèrera qu'un noeud n'est pas traité)
			tmpBool = false;
		tmpNode.setProcessed(tmpBool);

		// initialisation du parent = noeud du sommet de pile actuel
		Node tmpParent;
		tmpParent.clear();
		// BUG : il faut verifier que la pile ne soit pas vide
		if (!pile.empty())
			tmpParent = pile.top();
		setParent(tmpNode, tmpParent);
		addChild(tmpParent, tmpNode);

		numero++;
		setLastNumber(numero);

		// on empile le noeud ainsi initialisé
		pile.push(tmpNode);

		// on change de niveau
		niveau++;
	}

	// Si </Rule>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Rule")) == 0))
	{
		if (pile.empty())
			etat = ARuleTree;
		else
		{
			niveau--;
			Node noeud;
			noeud = pile.top();
			listNodes.add(noeud);

			pile.pop();
			etat = ARule;
		}
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteLeftSide(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	// Si <Item>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
	{
		nomItem = "";
		etat = ALSItem;
	}

	// Si </LeftSide>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("LeftSide")) == 0))
	{
		// on récupère le noeud de sommet de pile
		Node tmpNode = pile.top();
		pile.pop();
		// on initialise son attribut itemset
		tmpNode.setSetOfInt(ensItems);
		// puis on le rempile
		pile.push(tmpNode);
		etat = ARule;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteLSItem(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	if (xmlTextReaderNodeType(reader) == contenuBalise)
	{
		nomItem = (char *)(xmlTextReaderValue(reader));
		etat = ALSItem;
	}

	// Si </Item>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
	{
		ensItems.insert(tmpTable.getItemByName(nomItem));
		etat = ALeftSide;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraitePrincipalItem(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	if (xmlTextReaderNodeType(reader) == contenuBalise)
	{
		nomItem = (char *)(xmlTextReaderValue(reader));
		etat = APrincipalItem;
	}

	// Si </PrincipalItem>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("PrincipalItem")) == 0))
	{
		int tmp;
		tmp = tmpTable.getItemByName(nomItem);
		listNodesItem[pile.top()] = tmp;
		etat = ARule;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteRightSide(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	// Si <Item>
	if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
	{
		nomItem = "";
		etat = ARSItem;
	}

	// Si </RightSide>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("RightSide")) == 0))
	{
		// closure = leftside U rightside
		// on récupère le noeud du sommet de pile
		Node tmpNode = pile.top();
		pile.pop();
		SetOfInt tmpSetOfInt;
		tmpSetOfInt = tmpNode.getSetOfInt();
		SetOfInt tmpUnion;
		tmpUnion.clear();
		tmpUnion = tmpSetOfInt.I_union(ensItems);
		tmpNode.setClosure(tmpUnion);
		pile.push(tmpNode);
		etat = ARule;
	}
}


// --------------------------------------------------------------

void RuleTree::ATraiteRSItem(int & etat, xmlTextReaderPtr & reader, int & niveau, stack<Node> & pile, char * & nomItem, SetOfInt & ensItems, Table tmpTable)
{
	if (xmlTextReaderNodeType(reader) == contenuBalise)
	{
		nomItem = (char *)(xmlTextReaderValue(reader));
		etat = ARSItem;
	}

	// Si </Item>
	if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
	{
		ensItems.insert(tmpTable.getItemByName(nomItem));
		etat = ARightSide;
	}
}


// --------------------------------------------------------------


bool RuleTree::load()
{
	xmlTextReaderPtr reader = xmlNewTextReaderFilename(getName().c_str());
  if (reader != NULL)
  {
		Table tmpTable;
		Element tmpElement;

		stack<Node> pile;
		int ret = 1;
		int etat = ADebut;
		int niveau = 0;
		char * nomItem;
		SetOfInt ensItems;

		while ((ret == 1) && (etat != AFin))
		{
			ret = xmlTextReaderRead(reader);
			switch (etat)
			{
				case ADebut : ATraiteDebut(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ARuleTree : ATraiteRuleTree(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ARule : ATraiteRule(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ALeftSide : ATraiteLeftSide(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ALSItem : ATraiteLSItem(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case APrincipalItem : ATraitePrincipalItem(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ARightSide : ATraiteRightSide(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
				case ARSItem : ATraiteRSItem(etat, reader, niveau, pile, nomItem, ensItems, tmpTable); break;
			}
		}
		return (true);
	}
	return (false);
}


// ==============================================================

void RuleTree::saveRule(ofstream & fic, int num, Table tmpTable)
{
	//On sauvegarde les numéro en commençant à 0. En effet, les règles sont ensuite chargées sans tenir compte du numéro, dans cet ordre. L'interface doit cependant pouvoir recuperer le bon numéro.
	static int cur = 0;
	
	Node N = getNodeByNumber(num);

	fic << "<" << baliseRule << " support=\"" << N.getSupport();
	fic << "\" confidence=\"" << N.getConfidence();
	if (N.getSpecializable())
		fic << "\" specializable=\"yes\"";
	else
		fic << "\" specializable=\"no\"";
	if (N.getProcessed())
		fic << " processed=\"yes\"";
	else
		fic << " processed=\"no\"";
	
	fic << " number=\"" << cur++	<< "\"";
	fic << ">" << endl;

	// leftSide
	fic << "<" << baliseLeftSide << ">" << endl;
	set<int> tmpSetOfInt = N.getSetOfInt();
	set<int>::iterator itSetOfInt;
	string tmp;
	for (itSetOfInt = tmpSetOfInt.begin() ; itSetOfInt != tmpSetOfInt.end(); itSetOfInt++)
	{
		fic << "<" << baliseItem << ">";
		tmp = tmpTable.getNameOfItem(*itSetOfInt);
		fic << tmp;
		fic << "</" << baliseItem << ">" << endl;
	}
	fic << "</" << baliseLeftSide << ">" << endl;

	// PrincipalItem
	fic << "<" << balisePrincipalItem << ">";
	int tmpInt = getItemByNode(N);
	tmp = tmpTable.getNameOfItem(tmpInt).c_str();
	fic << tmp;
	fic << "</" << balisePrincipalItem << ">" << endl;

	// rightSide = closure\leftSide
	fic << "<" << baliseRightSide << ">" << endl;
	SetOfInt tmpRightSide;
	tmpRightSide.clear();
	tmpRightSide = (N.getClosure()).I_minus(N.getSetOfInt());
	tmpSetOfInt = tmpRightSide;
	for (itSetOfInt = tmpSetOfInt.begin() ; itSetOfInt != tmpSetOfInt.end() ; itSetOfInt++)
	{
		fic << "<" << baliseItem << ">";
		tmp = tmpTable.getNameOfItem(*itSetOfInt);
		fic << tmp;
		fic << "</" << baliseItem << ">" << endl;
	}
	fic << "</" << baliseRightSide << ">" << endl;

	set<int> tmpChildren;
	set<int>::iterator itChild;
	tmpChildren = getChildren(N);
	for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end() ; itChild++)
	{
		saveRule(fic, *itChild, tmpTable);
	}

	fic << "</" << baliseRule << ">" << endl;
}


// --------------------------------------------------------------

void RuleTree::save(string filename)
{
	if (filename != "")
	{
		ofstream fic;
		fic.open(filename.c_str());
		if (fic != NULL)
		{
			// on a besoin de la table associee
			Table tmpTable;
			tmpTable.setName(getTable());
			tmpTable.rewind();

			// en tete du fichier
			fic << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
			fic << "<!DOCTYPE RuleTree SYSTEM \"ruletree.dtd\">" << endl;
			fic << endl;

 			fic << "<" << baliseRuleTree << " table=\"" << getTable() << "\" supOrder =\"" << orderSup.getName() << "\" infOrder=\"" << orderInf.getName() << "\">" << endl;

			// pour chaque noeud racine (cad noeud n'ayant pas de pere)
			Node tmp;
			set<Node> tmpColl = listNodes.getCollection();
			set<Node>::iterator itColl;
			for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
			{
				tmp = getParent(*itColl);
				if (tmp.isNull())
				{
					saveRule(fic, itColl -> getNumber(), tmpTable);
				}

			}

			fic << "</" << baliseRuleTree << ">" << endl;

			//tmpTable.close();
			fic.close();
		}
	}
}


// ===========================================================

Node RuleTree::charToNode(string regle)
{
	Table tmpTable;
	tmpTable.setName(table);
	tmpTable.rewind();

	string item = "";
	int taille = regle.size();
	//int cpt = 0;
	int numItem = -1;
	SetOfInt tmp;
	int i = 0;

	while (i < taille)
	{
		if ((regle[i] != nameItem) && (regle[i] != implique))
		{
			item += regle[i];
		}
		else
		{
			if (regle[i] == nameItem)
			{
				numItem = tmpTable.getItemByName(item);
				tmp.insert(numItem);
				item = "";
				//cpt = 0;
				numItem = -1;
			}
			if (regle[i] == implique)
			{
				numItem = tmpTable.getItemByName(item);
				tmp.insert(numItem);
				item = "";
				//cpt = 0;
				numItem = -1;
			}
		}

		i++;
	}

	// item implique
	numItem = tmpTable.getItemByName(item);

	// traitement de chaine termine => recherche du noeud
	Node noeud;
	set<Node> tmpColl;
	set<Node>::iterator itColl;
	int num = -1;

	noeud.clear();
	tmpColl = listNodes.getCollection();

	if (!(tmp.empty()) &&(numItem != -1))
	{
		for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
		{
			if (tmp == (itColl -> getSetOfInt()))
			{
				num = getItemByNode(*itColl);
				if (num == numItem)
				{
					return (*itColl);
				}
			}
		}
	}

	return (noeud);
}


// ==============================================================

void RuleTree::addChild(Node N, Node child)
{
	// on doit ajouter child aux children de N
	SetOfInt tmpChildren;
	tmpChildren.clear();
	tmpChildren = getChildren(N);
	tmpChildren.insert(child.getNumber());
	setChildren(N, tmpChildren);

	// et on spécifie que child a pour parent N
	setParent(child, N);
}


// ==============================================================

void RuleTree::updateNode(Node N)
{
	int nodeNumber = N.getNumber();
	Node oldNode = listNodes.getNodeByNumber(nodeNumber);

	if (nodeNumber != -1)
	{
		// on doit mettre trois attribut a jour

		// listNodes
		listNodes.remove(oldNode);
		listNodes.add(N);

		// listNodesItem
		int item = getItemByNode(oldNode);
		listNodesItem.erase(oldNode);
		listNodesItem[N] = item;

		// parent
		Node pere = getParent(oldNode);
		if (!pere.isNull())
		{
			parent.erase(oldNode.getNumber());
			setParent(N, pere);
		}
	}
}


// ==============================================================

void RuleTree::insert(SetOfInt E, Node pere)
{
	Node tmpNode;
	SetOfInt tmp;

	// initialisation d'un noeud
	int tmpNum = getLastNumber();
	tmpNode.setNumber(tmpNum);
	tmpNode.setSetOfInt(E);
	tmpNode.setClosure(listItems);

	// initialisation de son parent
	if (!pere.isNull())
		setParent(tmpNode, pere);

	// initialisation de sa liste de fils
	tmp.clear();
	setChildren(tmpNode, tmp);

	// ajout de ce noeud aux children de pere
	if (!pere.isNull())
		addChild(pere, tmpNode);

	// ajout de ce noeud a listNodes
	listNodes.add(tmpNode);

	// ajout de ce noeud a listNodesItem
	// ce noeud implique le meme item que son pere
	if (!pere.isNull())
	{
		int tmpInt = getItemByNode(pere);
		listNodesItem[tmpNode] = tmpInt;
	}

	// mise a jour de lastNumber
	tmpNum++;
	setLastNumber(tmpNum);
}


// ==============================================================

void RuleTree::remove(Node N)
{
	Node tmpNode;
	int tmpInt;

	// suppression de tous ses fils, recursivement
	set<int> tmpSetOfInt;
	set<int>::iterator itSet;
	tmpSetOfInt.clear();
	tmpSetOfInt = getChildren(N);
	for (itSet = tmpSetOfInt.begin() ; itSet != tmpSetOfInt.end() ; itSet++)
	{
		tmpNode.clear();
		tmpNode = getNodeByNumber(*itSet);
		remove(tmpNode);
	}

	// suppression du noeud de la liste des fils de son pere
	SetOfInt tmpChildren;
	tmpChildren.clear();
	tmpNode.clear();
	tmpNode = getParent(N);
	if (!tmpNode.isNull())
	{
		tmpChildren = getChildren(tmpNode);
		tmpChildren.erase(N.getNumber());
		setChildren(tmpNode, tmpChildren);
	}

	tmpInt = N.getNumber();

	// liberation de la memoire dans children
	children.erase(tmpInt);

	// liberation de la memoire dans parent
	parent.erase(tmpInt);

	// suppression dans listNodes
	listNodes.remove(N);

	// suppression dans listNodesItem
	listNodesItem.erase(N);
}


// ==============================================================

void RuleTree::specialize(Node N)
{
	// si N est spécializable
	if (N.getSpecializable())
	{
		set<int> tmpChildren = getChildren(N);
		set<int>::iterator itChild;
		SetOfInt tmpSetOfInt;
		Element tmpElement;
		SetOfElements tmpSetOfElements;
		set<Element> tmpImPred;
		set<Element>::iterator itImPred;
		Node tmpNode;

		// Pour chaque fils de N
		for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end() ; itChild++)
		{
			// on doit avoir un SetOfElements
			tmpSetOfInt.clear();
			tmpSetOfInt = listNodes.getSetOfIntByNumber(*itChild);
			tmpSetOfElements.clear();
			tmpSetOfElements = itemsetToSetOfElements(tmpSetOfInt);

			tmpNode.clear();
			tmpNode = listNodes.getNodeByNumber(*itChild);
			tmpImPred = (orderSup.imPredIdeal(tmpSetOfElements)).getCollection();
			for (itImPred = tmpImPred.begin() ; itImPred != tmpImPred.end() ; itImPred++)
			{
				insert((itImPred -> getItemSet()), tmpNode);
			}
		}

		// Pour chaque tuple de la table
		Table tmpTable;
		tmpTable.setName(table);
		tmpTable.rewind(); // utilise la fonction readHeader()
		int nbTuples = tmpTable.getNbTuples();
		SetOfInt tmpTuple;
		SetOfNodes tmpSetOfNodes;

		for (int i = 0 ; i < nbTuples ; i++)
		{
			tmpTuple = tmpTable.readTuple();

			// on met a jour les fermes de tous les noeuds
			listNodes.updateClosureAll(tmpTuple);
		}

		//tmpTable.close();

		bool tmpBool = true;
		Node tmpChildNode;
		SetOfInt rightSide;
		int item;
		set<int> tmpSet;
		set<int>::iterator itSet;

		// Pour chaque fils de N
		for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end() ; itChild++)
		{
			tmpNode.clear();
			tmpNode = listNodes.getNodeByNumber(*itChild);
			tmpNode.setProcessed(tmpBool);
			tmpSet.clear();
			tmpSet = getChildren(tmpNode);

			item = 0;
			item = getItemByNode(tmpNode);

			// pour chaque fils des fils de N
			for (itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++)
			{
				tmpChildNode.clear();
				tmpChildNode = listNodes.getNodeByNumber(*itSet);
				rightSide.clear();
				rightSide = (tmpChildNode.getClosure()).I_minus(tmpChildNode.getSetOfInt());

				if (rightSide.find(item) != rightSide.end())
					tmpNode.setSpecializable(tmpBool);
				else
					remove(tmpChildNode);

				if (rightSide.empty())
					remove(tmpChildNode);
			}

			// on doit ensuite mettre tmpNode Ã  jour
			// listNodesItem, listNodes et parent sont a modifier => fonction updateNode
			updateNode(tmpNode);
		}
	}
}


// ==============================================================

bool RuleTree::jump(Node N)
{
	Node pere;
	pere = getParent(N);

	if ((pere.isNull()) && (N.getSpecializable()))
	{
		// le saut est possible
		set<int> tmpChildren = getChildren(N);
		set<int>::iterator itChild;
		Node tmpNode;
		// on commence par supprimer les fils existants
		// Pour chaque fils de N
		for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end() ; itChild++)
		{
			tmpNode.clear();
			tmpNode = listNodes.getNodeByNumber(*itChild);
			remove(tmpNode);
		}

		// calcul des infs maximaux
		Order O2;
		O2.clear();
		O2 = orderInf.duplicate();
		set<Element> tmpColl;
		set<Element>::iterator itColl;
		SetOfInt ens1, ens2;
		ens1 = N.getSetOfInt();

		tmpColl = (O2.getJ()).getCollection();
		// pour chaque element de la collection de O2
		for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
		{
			ens2 = itColl -> getItemSet();
			if (!(ens1.I_includes(ens2)))
			{
				O2.remove(*itColl);
			}
		}

		// parcours des maximaux
		SetOfElements maxIdeaux, tmpMax, tmpSoE;
		SetOfInt tmpSetOfInt;
		Element tmpElement;
		SetOfElements tmpSetOfElements;
		set<Element> tmp1;
		SetOfElements tmp2;
		set<Element>::iterator itTmp1, itTmp2, itTmp;
		SetOfInt tmpSet;
		int tmpInt;

		maxIdeaux.clear();
		tmpColl.clear();
		tmpColl = (O2.max()).getCollection();
		// pour chaque element des max de O2
		for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
		{
			tmpMax.clear();
			tmpSetOfElements.clear();
			tmpSetOfInt.clear();
			tmpSetOfInt = itColl -> getItemSet();
			tmpSetOfElements = itemsetToSetOfElements(tmpSetOfInt);

			// mais on doit avoir un SetOfElements complet ! => on le reforme
			tmp1.clear();
			tmp1 = tmpSetOfElements.getCollection();
			tmp2.clear();
			tmp2 = orderSup.getJ();
			for (itTmp1 = tmp1.begin() ; itTmp1 != tmp1.end() ; itTmp1++)
			{
				tmpSet.clear();
				tmpInt = itTmp1 -> getNumber();
				tmpSet = tmp2.getSetByNumber(tmpInt);
				itTmp1 -> setItemSet(tmpSet);
			}
			tmpSetOfElements.setCollection(tmp1);

			tmpSoE.clear();
			tmpSoE = orderSup.imSuccIdeal(tmpSetOfElements);
			tmpMax = maxIdeaux.unionSets(tmpSoE);
			maxIdeaux = tmpMax;
		}

		// insertion des maxIdeaux et de leurs predecesseurs dans l'arbo
		set<Element> tmpCollBis;
		set<Element>::iterator itCollBis;
		tmpColl.clear();
		tmpColl = maxIdeaux.getCollection();
		Node tmpChild;

		int item = getItemByNode(N);

		for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
		{
			insert(itColl -> getItemSet(), N);
			tmpSetOfElements.clear();
			tmpSetOfInt.clear();
			tmpSetOfInt = itColl -> getItemSet();
			tmpSetOfElements = itemsetToSetOfElements(tmpSetOfInt);

			// mais on doit avoir un SetOfElements complet ! => on le reforme
			tmp1.clear();
			tmp1 = tmpSetOfElements.getCollection();
			tmp2.clear();
			tmp2 = orderSup.getJ();
			for (itTmp1 = tmp1.begin() ; itTmp1 != tmp1.end() ; itTmp1++)
			{
				tmpSet.clear();
				tmpInt = itTmp1 -> getNumber();
				tmpSet = tmp2.getSetByNumber(tmpInt);
				itTmp1 -> setItemSet(tmpSet);
			}
			tmpSetOfElements.setCollection(tmp1);

			Node test;
			test.clear();
			tmpCollBis.clear();
			tmpCollBis = (orderSup.imPredIdeal(tmpSetOfElements)).getCollection();

			tmpNode.clear();
			tmpNode = getNodeByNumber(getLastNumber()-1);
			// pour chaque predecesseurs immediats de orderSup
			for (itCollBis = tmpCollBis.begin() ; itCollBis != tmpCollBis.end() ; itCollBis++)
			{
				if (!(tmpNode.isNull()))
					insert(itCollBis -> getItemSet(), tmpNode);
			}
		}

		// calcul des fermes
		Table tmpTable;
		tmpTable.setName(table);
		tmpTable.rewind();
		int nbTuples = tmpTable.getNbTuples();
		SetOfInt tmpTuple;
		SetOfNodes tmpSetOfNodes;

		// pour chaque tuple de la table
		for (int i = 0 ; i < nbTuples ; i++)
		{
			tmpTuple = tmpTable.readTuple();

// 			// pour chaque fils de N
// 			for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end(); itChild++)
// 			{
// 				tmpNode.clear();
// 				tmpNode = getNodeByNumber(*itChild);
// 				tmpSetOfInt.clear();
// 				tmpSetOfInt = getChildren(tmpNode);
// 				tmpSetOfNodes.clear();
// 				tmpSetOfNodes = itemsetToSetOfNodes(tmpSetOfInt);
// 				// on met a jour le ferme
// 				tmpSetOfNodes.updateClosureAll(tmpTuple);
// 			}
// 			tmpSetOfNodes.clear();
// 			tmpSetOfNodes = itemsetToSetOfNodes(getChildren(N));
// 			// on met a jour le ferme de N
// 			tmpSetOfNodes.updateClosureAll(tmpTuple);
			listNodes.updateClosureAll(tmpTuple);
		}

		//tmpTable.close();

		set<int> tmp;
		set<int>::iterator it;
		bool tmpBool = true;

		tmpChildren.clear();
		tmpChildren = getChildren(N);

		// pour chaque fils de N
		for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end(); itChild++)
		{
			tmpChild.clear();
			tmpChild = getNodeByNumber(*itChild);

			tmp = getChildren(tmpChild);
			// pour chaque fils des fils de N
			for (it = tmp.begin() ; it != tmp.end() ; it++)
			{
				tmpNode.clear();
				tmpNode = getNodeByNumber(*it);
				tmpSetOfInt.clear();
				tmpSetOfInt = (tmpNode.getClosure()).I_minus(tmpNode.getSetOfInt());
				// si l'item appartient a closure \ itemset alors ce fils de N est specializable
				if (tmpSetOfInt.find(item) != tmpSetOfInt.begin())
				{
					tmpChild.setSpecializable(tmpBool);
				}
				else
				{
					// sinon on supprime ce noeud
					remove(tmpNode);
				}
			}
			tmpChild.setProcessed(tmpBool);
			updateNode(tmpChild);

			tmpSetOfInt.clear();
			tmpSetOfInt = (tmpChild.getClosure()).I_minus(tmpChild.getSetOfInt());
			// si l'item n'appartient pas a closure \ itemset
			if (!(tmpSetOfInt.find(item) != tmpSetOfInt.end()))
			{
				// alors on supprime ce noeud
				remove(tmpChild);
			}
		}
		return (true);
	}
	else
		return (false);
}


// ==============================================================

void RuleTree::affiche()
{
	cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << endl;
	map<Node, int>::iterator itMap;
	map<int, Node>::iterator itMapN;
	map<int, SetOfNodes>::iterator itMapSoN;
	map<int, SetOfInt>::iterator itMapI;
	int tmp;
	set<int> tmpSet;
	set<int>::iterator itSet;
	set<Node> tmpColl;
	set<Node>::iterator it;

	cout << "listNodesItem : " << endl;
	for (itMap = listNodesItem.begin() ; itMap != listNodesItem.end() ; itMap++)
	{
		tmp = (itMap -> first).getNumber();
		cout << tmp << " => " << itMap -> second << endl;
	}
	cout << endl;

	cout << "listNodes : ";
	tmpColl = listNodes.getCollection();
	for (it = tmpColl.begin() ; it != tmpColl.end(); it++)
	{
		cout << " - " << it -> getNumber() << " - ";
	}
	cout << endl << endl;

	cout << "LeftSide de chaque noeud : " << endl;
	for (it = tmpColl.begin() ; it != tmpColl.end(); it++)
	{
		cout << it -> getNumber() << " : ";
		(it -> getSetOfInt()).affiche();
	}
	cout << endl;

	cout << "parent : " << endl;
	for (itMapN = parent.begin() ; itMapN != parent.end() ; itMapN++)
	{
		cout << "[" << itMapN -> first << "] = ";
		cout << "{";
		tmp = (itMapN -> second).getNumber();
		cout << tmp << "}" << endl;
	}
	cout << endl;

	cout << "children : " << endl;
	for (itMapI = children.begin() ; itMapI != children.end() ; itMapI++)
	{
		cout << "[" << itMapI -> first << "] = {";
		tmpSet = itMapI -> second;
		for (itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++)
		{
			cout << " - " << *itSet << " - ";
		}
		cout << "}" << endl;
	}
	cout << endl;

	cout << "table : " << table << endl;
	cout << endl;

	cout << "orderSup : " << endl;
	orderSup.affiche();
	cout << endl;

	cout << "orderInf : " << endl;
	orderInf.affiche();
	cout << endl;

	cout << "lastNumber : " << getLastNumber() << endl;
	cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << endl;
}

// ==============================================================

void RuleTree::afficheBis()
{
	cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << endl;
	map<Node, int>::iterator itMap;
	map<int, Node>::iterator itMapN;
	map<int, SetOfNodes>::iterator itMapSoN;
	map<int, SetOfInt>::iterator itMapI;
	int tmp;
	set<int> tmpSet;
	set<int>::iterator itSet;
	set<Node> tmpColl;
	set<Node>::iterator it;

	cout << "listNodesItem : " << endl;
	for (itMap = listNodesItem.begin() ; itMap != listNodesItem.end() ; itMap++)
	{
		tmp = (itMap -> first).getNumber();
		cout << tmp << " => " << itMap -> second << endl;
	}
	cout << endl;

	cout << "listNodes : ";
	tmpColl = listNodes.getCollection();
	for (it = tmpColl.begin() ; it != tmpColl.end(); it++)
	{
		it -> affiche();
	}
	cout << endl << endl;

	cout << "table : " << table << endl;
	cout << endl;

	cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << endl;
}

