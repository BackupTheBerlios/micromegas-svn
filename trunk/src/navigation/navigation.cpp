/********************************************************/
/* Application : Fouille de donnees			*/
/* Nom du fichier : navigation.cpp			*/
/* Derniere mise a jour : 23/07/2004			*/
/* Auteur : Noyer Caroline				*/
/********************************************************/ 


#include "navigation.hpp"


// ===========================================================
// Calcule l'ordre des inf-irreductibles a partir de la table
// dont le nom de fichier est passe en parametre
// Retourne l'ordre ainsi créé
// ===========================================================

Order ordreInf(char * filename)
{
	Order INF;
	INF.clear();
	int num = 1;
	Table tmpTable;
	int nbTuples = 0;
	SetOfInt tmpTuple;
	Element tmpElement;
	SetOfInt inter;
	SetOfInt tmpInter;
	set<Element> tmpSetOfElements, tmpSetOfElementsBis;
	set<Element>::iterator itSoE, itSoEBis;
	
	tmpTable.setName(filename);
	tmpTable.rewind();
	
	nbTuples = tmpTable.getNbTuples();
	for (int i = 0 ; i < nbTuples ; i++)
	{
		tmpTuple.clear();
		tmpTuple = tmpTable.readTuple();
		
		tmpElement.setItemSet(tmpTuple);
		tmpElement.setNumber(num);
		num++;
		INF.insert(tmpElement);
		inter.clear();
		inter = tmpTable.getListItems();
		
		// pour chaque successeur de tmpElement
		tmpSetOfElements.clear();
		tmpSetOfElements = (INF.getImSucc(tmpElement)).getCollection();
		for (itSoE = tmpSetOfElements.begin() ; itSoE != tmpSetOfElements.end() ; itSoE++)
		{
			tmpInter = inter.I_intersection(itSoE -> getItemSet());
			inter = tmpInter;
		}
		
		if (inter == tmpTuple)
		{
			INF.remove(tmpElement);
		}
		else
		{
			tmpSetOfElements.clear();
			tmpSetOfElements = (INF.getImPred(tmpElement)).getCollection();
			for (itSoE = tmpSetOfElements.begin() ; itSoE != tmpSetOfElements.end() ; itSoE++)
			{
				inter.clear();
				inter = tmpTable.getListItems();
				
				tmpSetOfElementsBis = (INF.getImSucc(*itSoE)).getCollection();
				for (itSoEBis = tmpSetOfElementsBis.begin() ; itSoEBis != tmpSetOfElementsBis.end() ; itSoEBis++)
				{
					tmpInter = inter.I_intersection(itSoEBis -> getItemSet());
					inter = tmpInter;
				}
				if (inter == (itSoE -> getItemSet()))
				{
					INF.remove(*itSoE);
				}
			}
		}

	}
	//tmpTable.close();
	
	return (INF);
}


// ===========================================================
// Calcule l'ordre des sup-irreductibles a partir de la table
// dont le nom de fichier est passe en parametre
// Retourne l'ordre ainsi créé
// ===========================================================

Order ordreSup(char * filename)
{
	Order SUP;
	SetOfElements liste;
	Table table;
	set<int> tmpSetOfInt;
	set<int>::iterator itSet;
	SetOfInt tmpSet;
	Element tmpElement;
	set<Element> tmpSoE;
	set<Element>::iterator itSoE;
	
	liste.clear();
	table.setName(filename);
	table.rewind();
	
	tmpSetOfInt = table.getListItems();
	tmpSet = table.getListItems();
	for (itSet = tmpSetOfInt.begin() ; itSet != tmpSetOfInt.end() ; itSet++)
	{
		tmpElement.clear();
		tmpElement.setNumber(*itSet);
		// l'ensemble associe est vide
		tmpElement.setItemSet(tmpSet);
		liste.add(tmpElement);
	}
	//table.close();
	
	liste.closureAll(filename);
	SUP.clear();
	
	tmpSoE.clear();
	tmpSoE = liste.getCollection();
	
	for (itSoE = tmpSoE.begin() ; itSoE != tmpSoE.end() ; itSoE++)
	{
		SUP.insert(*itSoE);
	}
	
	return (SUP);
}


// ===========================================================
// Cas d'utilisation = Initialisation de l'arborescence
// => Creation de la premiere arborescence de regles
// 
// La table correspondante doit être disponible
//
// - Calcule l'ordre des sup, l'ordre des inf, les regles triviales
// et les regles generales
// - Sauvegarde les ordres et l'arborescence dans les fichiers XML
//
// en parametre = le nom du fichier XML contenant la table
// ===========================================================

void initArbo(char * filename)
{
	if (filename != "")
	{
		int taille = strlen(filename)-4;
		
		// calcul de l'ordre des sup
		// ---------------------------------------------------------
		char * nameSup;
		nameSup = (char*)malloc(taille*sizeof(char));
		strncpy(nameSup, filename, taille);
		int taille2 = strlen(filename);
		char * newNameSup;
		newNameSup = (char*)malloc(taille2*sizeof(char));
		newNameSup = strcat(nameSup, "_sup.xml");
		Order SUP;
		SUP.clear();
		SUP = ordreSup(filename);
		SUP.setName(newNameSup);
		SUP.setTable(filename);
		SUP.save();

		// calcul de l'ordre des inf
		// ---------------------------------------------------------
		char * nameInf;
		nameInf = (char*)malloc(taille*sizeof(char));
		strncpy(nameInf, filename, taille);
		char * newNameInf;
		newNameInf = (char*)malloc(taille2*sizeof(char));
		newNameInf = strcat(nameInf,"_inf.xml");
		Order INF;
		INF.clear();
		INF = ordreInf(filename);
		INF.setName(newNameInf);
		INF.setTable(filename);
		INF.save();
		
		// initialisation de l'arborescence
		// ---------------------------------------------------------
	
		char * nameArbo;
		nameArbo = (char*)malloc(taille*sizeof(char));
		strncpy(nameArbo, filename, taille);
		char * newNameArbo;
		newNameArbo = (char *)malloc(taille2*sizeof(char));
		newNameArbo = strcat(nameArbo,"_arbo.xml");
		
		RuleTree tmpRuleTree;
		tmpRuleTree.clear();
		Node noeudNull;
		noeudNull.clear();
		bool boolTrue = true;
		bool boolFalse = false;
		
		tmpRuleTree.setName(newNameArbo);
		tmpRuleTree.setTable(filename);
		
		tmpRuleTree.setOrderSup(SUP);
		
		// regles triviales
		// ---------------------------------------------------------
		set<Element> tmpColl, tmpImPred;
		set<Element>::iterator itColl, itImPred;
		SetOfInt tmpSet;
		Node currentNode;
		int numero;
		tmpColl.clear();
		tmpColl = (SUP.getJ()).getCollection();
		
		for (itColl = tmpColl.begin() ; itColl != tmpColl.end() ; itColl++)
		{
			tmpImPred.clear();
			tmpImPred = (SUP.getImPred(*itColl)).getCollection();
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
			copieOrdre = SUP.removeFilter(*itColl);
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
		
		tmpRuleTree.save(newNameArbo);
	}
	
}


// ===========================================================

void specialiser(char * filename)
{}


// ===========================================================

void sauter(char * filename)
{}


// ===========================================================

