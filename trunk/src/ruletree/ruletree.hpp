/********************************************************/
/* Application : Fouille de donnees			*/
/* Nom du fichier : ruletree.hpp			*/
/* Derniere mise a jour : 23/07/2004			*/
/* Auteur : Noyer Caroline				*/
/********************************************************/ 


#ifndef __RULETREE_HPP__
#define __RULETREE_HPP__

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <set>
#include <algorithm>
#include <stack>

#include "../order/setofint.hpp"
#include "setofnodes.hpp"
#include "../order/order.hpp"

using namespace std;

/*
 * Classe RuleTree
 * Classe qui definit une arborescence de regles
 * @author NOYER Caroline
 */

class RuleTree
{
	protected:
		/** l'entier permet d'indiquer l'item implique�par le noeud (partie droite de la regle) */
		map<Node, int> listNodesItem;

		/** un ensemble de noeuds */
		SetOfNodes listNodes;

		/** parent d'un noeud */
		map<int, Node> parent;

		/** fils d'un noeud */
		map<int, SetOfInt> children;
		
		/** nom du fichier XML */
		string name;

		/** nom de la table XML associee */
		string table;

		/** l'ordre des sup-irreductibles */
		Order orderSup;

		/** l'ordre des inf-irreductibles */
		Order orderInf;

		/** dernier numero attribue a un noeud */
		int lastNumber;
		
		/** ensemble des items (contenus dans la table) */
		SetOfInt listItems;

	public :
		/**
		  * Constructeur par defaut d'une arborescence
		  */
		RuleTree();

		/**
		  * Constructeur de recopie
		  */
		RuleTree(const RuleTree &);

		/**
		  * Destructeur
		  */
		~RuleTree();

		/**
		  * Fonction qui remet l'arborescence a zero
		  */
		void clear();

		/**
		  * Fonction qui initialise l'attribut listNodesItem
		  * @param un objet de type map
		  */
		void setListNodesItem(map<Node, int>);
		
		/**
		  * Fonction qui recupere la liste des noeuds et l'item qu'ils impliquent
		  */
		map<Node, int> getListNodesItem() const;

		/**
		  * Fonction qui initialise l'attribut listNodes
		  * @param un ensemble de noeuds (SetOfNodes)
		  */
		void setListNodes(SetOfNodes);
		
		/**
		  * Fonction qui recupere la liste des noeuds
		  */
		SetOfNodes getListNodes() const;

		/**
		  * Fonction qui initialise l'attribut parent
		  * @param le noeud pour lequel on veut initialiser le parent
		  * @param le pere de ce noeud
		  */
		void setParent(Node, Node);
		
		/**
		  * Fonction qui recupere le pere d'un noeud
		  * @param le noeud dont on veut le pere
		  */
		Node getParent(Node);

		/**
		  * Fonction qui initialise l'attribut children
		  * @param le noeud pour lequel on veut initialiser les fils
		  * @param l'ensemble des fils sous forme d'SetOfInt
		  */
		void setChildren(Node, SetOfInt);
		
		/**
		  * Fonction qui recupere les fils d'un noeud
		  * @param le noeud dont on veut les fils
		  */
		SetOfInt getChildren(Node);
		
		/**
		  * Fonction qui initialise l'attribut name
		  * @param le nom du fichier XML contenant l'arborescence
		  */
		void setName(string);
		
		/**
		  * Fonction qui recupere le nom du fichier correspondant
		  */
		string getName() const;

		/**
		  * Fonction qui initialise l'attribut table
		  * @param le nom du fichier XML contenant la table correspondante
		  */
		void setTable(string);
		
		/**
		  * Fonction qui recupere le nom de la table correspondante
		  */
		string getTable() const;

		/**
		  * Fonction qui initialise l'attribut orderSup
		  * @param l'ordre avec lequel on initialise
		  */
		void setOrderSup(Order);
		
		/**
		  * Fonction qui recupere l'ordre des sup-irreductibles
		  */
		Order getOrderSup() const;

		/**
		  * Fonction qui initialise l'attribut orderInf
		  * @param l'ordre avec lequel on initialise
		  */
		void setOrderInf(Order);
		
		/**
		  * Fonction qui recupere l'ordre des inf-irreductibles
		  */
		Order getOrderInf() const;

		/**
		  * Fonction qui initialise l'attribut lastNumber
		  * @param le dernier numero attribue
		  */
		void setLastNumber(int);
		
		/**
		  * Fonction qui recupere le dernier numero attribue
		  */
		int getLastNumber() const;
		
		/**
		  * Fonction qui initialise l'attribut listItems
		  * @param l'ensemble de items presents
		  */
		void setListItems(SetOfInt);
		
		/**
		  * Fonction qui recupere l'ensemble des items
		  */
		SetOfInt getListItems() const;
		
		/**
		  * Fonction qui initialise l'item implique par un noeud
		  */
		void setNodeItem(Node, int);
		
		/**
		  * Fonction qui recupere l'item implique par un noeud
		  * @param le noeud pour lequel on veut l'item
		  */
		int getItemByNode(Node);
		
		/**
		  * Fonction qui recupere un noeud par son numero
		  * @param le numero du noeud que l'on veut recuperer
		  */
		Node getNodeByNumber(int);
		
		/**
		  * Fonction qui retourne l'ensemble des numeros des noeuds presents dans l'arborescence
		  */
		SetOfInt getNodesNumbers();
		
		/**
		  * Fonction qui convertit un SetOfInt en SetOfElements
		  * @param l'ensemble que l'on veut convertir
		  */
		SetOfElements itemsetToSetOfElements(SetOfInt);
		
		/**
		  * Fonction qui convertit un SetOfInt en SetOfNodes
		  * @param l'ensemble que l'on veut convertir
		  */
		SetOfNodes itemsetToSetOfNodes(SetOfInt);

		/**
		  * Fonction de traitements pour l'automate
		  * @param l'etat actuel de l'automate (qui sera eventuellement modifie)
		  * @param le reader XML (qui sera lui aussi modifie)
		  * @param le niveau du noeud courant dans l'arborescence
		  * @param la pile des noeuds en cours de traitement
		  * @param le nom de l'item courant
		  * @param l'ensemble d'items courant
		  * @param la table associee a cette arborescence
		  */
		void ATraiteDebut(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table &);
		void ATraiteRuleTree(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraiteRule(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraiteLeftSide(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraiteLSItem(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraitePrincipalItem(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraiteRightSide(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);
		void ATraiteRSItem(int &, xmlTextReaderPtr &, int &, stack<Node> &, char * &, SetOfInt &, Table);

		/**
		  * Fonction qui charge la structure
		  */
		bool load();

		/**
		  * Fonction qui sauvegarde la structure
		  * @param le nom du fichier XML
		  */
		void saveRule(ofstream &, int, Table);
		void save(string);
		
		/**
		  * Fonction qui transforme une regle sous forme de chaine de caracteres en Node
		  * @param la regle
		  * @param la table associee a cette arborescence
		  */
		Node charToNode(string);

		/**
		  * Fonction qui ajoute un fils �un noeud de l'arborescence
		  * @param le noeud auquel on ajoute un fils
		  * @param le noeud a�ajouter
		  */
		void addChild(Node, Node);
		
		/**
		  * Fonction qui met a jour un noeud
		  * @param le noeud que l'on doit mettre a jour
		  */
		void updateNode(Node);

		/**
		  * Fonction qui insere un noeud dans l'arborescence
		  * @param l'itemset de ce noeud
		  * @param son pere
		  */
		int insert(SetOfInt, Node);

		/**
		  * Fonction qui supprime un noeud de l'arborescence
		  * @param le noeud a supprimer
		  */
		void remove(Node);

		/**
		  * Fonction qui specialise un noeud de l'arborescence
		  * @param le noeud
		  */
		void specialize(Node);

		/**
		  * Fonction qui effectue un saut dans l'arborescence
		  * @param un noeud
		  */
		bool jump(Node);
	
		/**
		  * Fonction d'affichage d'un objet de type RuleTree
		  */
		void affiche();
		void afficheBis();
};


#endif // __RULETREE_HPP__
