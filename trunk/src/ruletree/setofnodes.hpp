/********************************************************/
/* Application : Fouille de donnees			*/
/* Nom du fichier : setOfNodes.hpp			*/
/* Derniere mise a jour : 23/07/2004			*/
/* Auteur : Noyer Caroline				*/
/********************************************************/


#ifndef __SETOFNODES_HPP__
#define __SETOFNODES_HPP__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#include <libxml/xmlreader.h>

#include <map>
#include <algorithm>

#include "../order/table.hpp"
#include "node.hpp"

using namespace std;

/*
 * Classe SetOfNodes
 * Classe qui definit un ensemble de noeuds
 * @author NOYER Caroline
 */

class SetOfNodes
{
	protected:
		/** un ensemble de noeuds */
		set<Node> collection;

	public:
		/**
		  * Constructeur par defaut d'un setOfNodes
		  */
		SetOfNodes();

		/**
		  * Constructeur de recopie
		  */
		SetOfNodes(const SetOfNodes &);

		/**
		  * Destructeur
		  */
		~SetOfNodes();

		/**
		  * Fonction qui efface les noeuds de la collection
		  */
		void clear();

		/**
		  * Surcharge de l'operateur =
		  */
		SetOfNodes & operator=(const SetOfNodes &);

		/**
		  * Surcharge de l'operateur !=
		  */
		bool operator!=(SetOfNodes);

		/**
		  * Surcharge de l'operateur ==
		  */
		bool operator==(SetOfNodes);

		/**
		  * Fonction qui initialise l'attribut collection
		  * @param un ensemble de noeuds constituant la collection
		  */
		void setCollection(set<Node>);

		/**
		  * Fonction qui retourne la collection
		  */
		set<Node> getCollection() const;

		/**
		  * Fonction qui ajoute un noeud a la collection
		  * @param le noeud a ajouter
		  */
		void add(Node);

		/**
		  * Fonction qui supprime un noeud de la collection
		  * @param le noeud a supprimer
		  */
		void remove(Node);

		/**
		  * Fonction qui recupere un noeud par son itemset
		  * @param l'itemset du noeud de type SetOfInt
		  */
		Node getNodeBySetOfInt(SetOfInt);

		/**
		  * Fonction qui recupere un noeud par son numero
		  * @param l'entier correspondant au numero du noeud
		  */
		Node getNodeByNumber(int);
		
		/** 
		  * Fonction qui recupere l'itemset d'un noeud par le numero du noeud
		  * @param le numero du noeud dont on veut l'itemset
		  */
		SetOfInt getSetOfIntByNumber(int);

		/**
		  * Fonction qui met a jour tous les attributs closure des noeuds de la collection
		  * @param l'ensemble avec lequel on effectue l'intersection pour mettre a jour
		  */
		void updateClosureAll(SetOfInt);

		/**
		  * Fonction qui
		  * @param
		  */
		//void closureAll(char *);

		/**
		  * Definition d'un iterateur sur le TDA SetOfNodes
		  */
		// en fait il suffit de definir l'iterateur sur la collection, de type set<Node>
		typedef set<Node>::iterator SoN_iterator;
		SoN_iterator begin() {return (collection.begin());}
		SoN_iterator end() {return (collection.end());}

		/**
		  * Fonction d'affichage d'un objet de type SetOfNodes
		  */
		void affiche();
};


#endif // __SETOFNODES_HPP__
