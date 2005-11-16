/********************************************************/
/* Application : Fouille de donnees                     */
/* Nom du fichier : navigation.cpp                      */
/* Derniere mise a jour : 23/07/2004                    */
/* Auteur : Noyer Caroline                              */
/********************************************************/


#include "navigation.hpp"

// ===========================================================
// Cas d'utilisation = Initialisation de l'arborescence
// => Creation de la premiere arborescence de regles
//
// La table correspondante doit etre disponible
//
// - Calcule l'ordre des sup, l'ordre des inf, les regles triviales
// et les regles generales
// - Sauvegarde les ordres et l'arborescence dans les fichiers XML
//
// en parametre = le nom du fichier XML contenant la table
// ===========================================================
void initArbo(string filename)
{
	string name = filename.substr(0,filename.find_first_of("."));
	if (name.size() == 0) {
		cout << "Erreur de nom de fichier" <<endl;
		exit(0);
	}

	/// Calcul de l'odre des sup.
	SetOfElements soeSup;
	soeSup.setSup(filename);
	soeSup.setName(name + ".collection.sup.xml");
	soeSup.setTable(filename);
	Order ordSup;
	ordSup.setJ(soeSup);
	ordSup.save();
	ordSup.genGraph(name + ".sup.dot");

	/// Calcul de l'odre des inf.
	SetOfElements soeInf;
	soeInf.setInf(filename);
	soeInf.setName(name + ".collection.inf.xml");
	soeInf.setTable(filename);
	Order ordInf;
	ordInf.setJ(soeInf);
	ordInf.save();
	ordInf.genGraph(name + ".inf.dot");

	/// Initialisation de l'arborescence

	RuleTree tmpRuleTree;
	tmpRuleTree.clear();
	Node noeudNull;
	noeudNull.clear();
	bool boolTrue = true;
	bool boolFalse = false;

	tmpRuleTree.setName(name + ".arbo.xml");
	tmpRuleTree.setTable(filename);

	tmpRuleTree.setOrderSup(ordSup);
	tmpRuleTree.setOrderInf(ordInf);

    // ecrit aussi la DTD
    makeRuletreeDTD(filename);

	// regles triviales
	// ---------------------------------------------------------
	set<Element> tmpColl, tmpImPred;
	set<Element>::iterator itColl, itImPred;
	SetOfInt tmpSet;
	Node currentNode;
	int numero;
	tmpColl.clear();
	tmpColl = (ordSup.getJ()).getCollection();

	for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
	{
		tmpImPred.clear();
		tmpImPred = (ordSup.getImPred(*itColl)).getCollection();
		for (itImPred = tmpImPred.begin() ; itImPred != tmpImPred.end() ; itImPred++)
		{
			tmpSet.clear();
			tmpSet.insert(itColl -> getNumber());
			tmpRuleTree.insert(tmpSet, noeudNull);
			numero = 0;
			numero = tmpRuleTree.getLastNumber() - 1;
			currentNode.clear();
			currentNode = tmpRuleTree.getNodeByNumber(numero);
			tmpSet.clear();
			tmpSet = itColl -> getItemSet();
			currentNode.setClosure(tmpSet);
			currentNode.setSpecializable(boolFalse);
			currentNode.setProcessed(boolTrue);
			tmpRuleTree.updateNode(currentNode);
			tmpRuleTree.setNodeItem(currentNode, itImPred -> getNumber());

		}
	}

	// regles generales
	Table tmpTable;
	tmpTable.clear();
	tmpTable.setName(filename);
	tmpTable.rewind();

	SetOfInt tmpListItems;
	tmpListItems.clear();
	tmpListItems = tmpTable.getListItems();
	tmpRuleTree.setListItems(tmpListItems);

	Order copieOrdre;
	SetOfInt tmpSetOfInt;
	set<Element> tmpSetOfElements;
	set<Element>::iterator itSetOfElements;
	SetOfElements tmpImPredIdeal;
	Node tmpParent;
	int lastNode;
	for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
	{
		copieOrdre.clear();
		copieOrdre = ordSup.removeFilter(*itColl);
		tmpSet.clear();
		tmpSet = copieOrdre.getJnumbers();
		tmpRuleTree.insert(tmpSet, noeudNull);
		numero = 0;
		numero = tmpRuleTree.getLastNumber() - 1;
		currentNode.clear();
		currentNode = tmpRuleTree.getNodeByNumber(numero);
		tmpRuleTree.setNodeItem(currentNode, itColl -> getNumber());

		// insertion des fils
		tmpSetOfInt.clear();
		tmpSetOfElements.clear();
		tmpSetOfInt = copieOrdre.getJnumbers();
		lastNode = tmpRuleTree.getLastNumber() - 1;
		tmpParent.clear();
		tmpParent = tmpRuleTree.getNodeByNumber(lastNode);
		tmpImPredIdeal.clear();
		tmpImPredIdeal = copieOrdre.imPredIdeal(tmpRuleTree.itemsetToSetOfElements(tmpSetOfInt));
		tmpSetOfElements.clear();
		tmpSetOfElements = tmpImPredIdeal.getCollection();
		for (itSetOfElements = tmpSetOfElements.begin() ; itSetOfElements != tmpSetOfElements.end() ; itSetOfElements++)
		{
			tmpRuleTree.insert(itSetOfElements -> getItemSet(), tmpParent);
		}
	}

	// on doit maintenant mettre l'ensemble des fermes de chaque noeud a jour
	// lecture du fichier contenant la table
	int nbTuples = 0;
	SetOfInt tmpTuple;
	SetOfNodes tmpListNodes;
	tmpListNodes.clear();
	tmpListNodes = tmpRuleTree.getListNodes();

	nbTuples = tmpTable.getNbTuples();
	for (int i = 0 ; i < nbTuples ; i++)
	{
		tmpTuple.clear();
		tmpTuple = tmpTable.readTuple();
		tmpListNodes.updateClosureAll(tmpTuple);
	}

	//tmpTable.close();

	// on supprime ceux qui sont des fermes
	set<Node> tmpCollListNodes;
	set<Node>::iterator itListNodes;
	tmpCollListNodes.clear();
	tmpCollListNodes = tmpListNodes.getCollection();
	for (itListNodes = tmpCollListNodes.begin() ; itListNodes != tmpCollListNodes.end() ; itListNodes++)
	{
		if (!(itListNodes -> getProcessed()))
		{
			if ((itListNodes -> getSetOfInt()) == (itListNodes -> getClosure()))
			{
				tmpRuleTree.remove(*itListNodes);
			}
		}
	}

	// Traitement pour les regles generales uniquement
	set<int> tmpChildren;
	set<int>::iterator itChild;
	Node tmpNode;
	int item;
	SetOfInt ens;
	bool vrai = true;
	tmpCollListNodes.clear();
	tmpCollListNodes = (tmpRuleTree.getListNodes()).getCollection();
	for (itListNodes = tmpCollListNodes.begin() ; itListNodes != tmpCollListNodes.end() ; itListNodes++)
	{
		if (((tmpRuleTree.getParent(*itListNodes)).isNull()) && (!(itListNodes -> getProcessed())))
		{
			tmpChildren.clear();
			tmpChildren = tmpRuleTree.getChildren(*itListNodes);
			for (itChild = tmpChildren.begin() ; itChild != tmpChildren.end() ; itChild++)
			{
				tmpNode = tmpRuleTree.getNodeByNumber(*itChild);
				item = tmpRuleTree.getItemByNode(*itListNodes);
				ens = (tmpNode.getClosure()).I_minus(tmpNode.getSetOfInt());
				if (ens.find(item) != ens.end())
					itListNodes -> setSpecializable(vrai);
			}
		}
		itListNodes -> setProcessed(vrai);
	}

	tmpListNodes.setCollection(tmpCollListNodes);
	tmpRuleTree.setListNodes(tmpListNodes);

	tmpRuleTree.save(name + ".arbo.xml");
}


// ===========================================================
void specialiser(string filename) {
}

void specialiser(string input,int node, string output) {
	RuleTree rt;
	rt.setName(input);
	rt.load();
	rt.specialize(rt.getNodeByNumber(node));
	rt.save(output);
}


// ===========================================================
void sauter(string filename) {
}



// ===========================================================
// Wrapper des fonctions precedantes avec des parametres
// compatible RPC
void initArbo(char* filename) {
    string name(filename);
    initArbo(name);
}

void specialiser(char* filename) {
    string name(filename);
    specialiser(name);
}

void sauter(char* filename) {
    string name(filename);
    sauter(name);
}


// ===========================================================
// Cree la DTD "ruletree.dtd" dans le dossier du fichier "filename".
void makeRuletreeDTD(string filename) {
    string destdtd = "";
    if (filename.find_last_of("/") < filename.size()) {
        destdtd = filename.substr(0, filename.find_last_of("/")) + "/";
    }
    destdtd += "ruletree.dtd";
    cout << destdtd << endl;

    ofstream os(destdtd.c_str());

    os << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;

    os << "<!ELEMENT RuleTree (Rule+) >" << endl;
    os << "<!ELEMENT Rule (LeftSide+, Item+, RightSide+, Rule*) >" << endl;
    os << "<!ELEMENT LeftSide (Item+) >" << endl;
    os << "<!ELEMENT RightSide (Item+) >" << endl;
    os << "<!ELEMENT PrincipalItem (#PCDATA) >" << endl;
    os << "<!ELEMENT Item (#PCDATA) >" << endl;

    os << "<!ATTLIST RuleTree table CDATA #REQUIRED>" << endl;
    os << "<!ATTLIST RuleTree supOrder CDATA #REQUIRED>" << endl;
    os << "<!ATTLIST RuleTree infOrder CDATA #REQUIRED>" << endl;

    os << "<!ATTLIST Rule support CDATA #REQUIRED>" << endl;
    os << "<!ATTLIST Rule confidence CDATA #REQUIRED>" << endl;
    os << "<!ATTLIST Rule specializable CDATA #REQUIRED>" << endl;
    os << "<!ATTLIST Rule processed CDATA #REQUIRED>" << endl;

    os.close();
}
