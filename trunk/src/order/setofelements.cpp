/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : setOfElement.cpp      */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#include "setofelements.hpp"

#define baliseCollection "Collection"
#define baliseElement "Element"
#define baliseNumber "Number"
#define baliseSet "Set"
#define baliseItem "Item"

#define baliseOuvrante 1
#define contenuBalise 3
#define baliseFermante 15

#define SoEDebut 0
#define SoECollection 1
#define SoEElement 2
#define SoENumber 3
#define SoESet 4
#define SoEItem 5
#define SoEFin 6

// ==============================================================

SetOfElements::SetOfElements()
{
  collection.clear();
  name = "";
  table = "";
}


// ==============================================================

SetOfElements::SetOfElements(const SetOfElements & init)
{
  collection = init.collection;
  name = init.name;
  table = init.table;
}


// ==============================================================

SetOfElements::~SetOfElements()
{
}

// ==============================================================

void SetOfElements::setSup(const string & fichier) {
  Table tbl;
  tbl.setName(fichier);
  table = fichier;
	tbl.rewind();
  
  for (SetOfInt::iterator it = tbl.getListItems().begin() ;
      it != tbl.getListItems().end();
      it++) {
      SetOfInt s;
      Element tmpElement(*it,s);
      add(tmpElement);
  }
  closureAll(fichier);
}

// ==============================================================

void SetOfElements::setInf(const string & fichier) {
  Table tbl;
  tbl.setName(fichier);
	tbl.rewind();
  SetOfInt item = tbl.getListItems();
  
  map<int,SetOfElements> Meet;
  
  for (int nbtuples = 0 ; nbtuples < tbl.getNbTuples() ; ++nbtuples) {
    SetOfInt tuple = tbl.readTuple();
    //cout << "Tuple en cours : " << nbtuples << endl;
    for(SetOfInt::iterator xi = item.begin(); xi != item.end(); ++xi) {
      
      //cout << *xi << " appartient au tuple ";
      //tuple.affiche();
      
      if (tuple.find(*xi) == tuple.end()) {
        
        //cout << "\tNon, SOE concerné : " << endl;
        //Meet[*xi].affiche();
        
        bool ok = true;
        for(SoE_iterator element = Meet[*xi].begin();
            element != Meet[*xi].end(); ++element) {
          
          //element->affiche();
          //cout << " inclus dans le tuple ?" << endl;
              
          if (tuple.I_includes(element->getItemSet())) {
            if (element->getItemSet().size() != tuple.size()) {
              //cout << "\tOui, on supprime l'element ";
              //element->affiche();
              Meet[*xi].remove(*element);
            }
          }
          
          //cout << "le tuple dans l'element ?" << endl;
          
          if (element->getItemSet().I_includes(tuple)) {
            //cout << "\tOui." << endl;
            ok = false;
            break;
          }
        }
        //cout << "On insere le tuple ?" << endl;
        if (ok) {
          //cout << "\tOui." << endl;
          Element ins(Meet[*xi].getNextAvailableNumber(),tuple);
          Meet[*xi].add(ins);
        }
      }
    }
  }

  // Les fonctions d'unions existantes ne fonctionnent pas. J'en crée une nouvelle.
  set<SetOfInt> cont;
  for(SetOfInt::iterator xi = item.begin();
    xi != item.end(); ++xi) {
    //cout << getName() + ".collection." + tbl.getNameOfItem(*xi) + ".inf.xml" << endl;
    Meet[*xi].setName(getName() + ".collection." + tbl.getNameOfItem(*xi) + ".inf.xml");
    Meet[*xi].setTable(getTable());
    Meet[*xi].save();
  }
}

// ==============================================================

void SetOfElements::clear()
{
  collection.clear();
  name = "";
  table = "";
}


// ==============================================================

SetOfElements& SetOfElements::operator=(const SetOfElements & init)
{
  //collection = tmp.collection;
  SoE_iterator itSet;
  SetOfElements tmp = init;

  for (itSet = tmp.begin() ; itSet != tmp.end() ; itSet++)
  {
    this -> add(*itSet);
  }

  name = tmp.name;
  table = tmp.table;

  return (*this);
}


// ==============================================================

bool SetOfElements::operator!=(SetOfElements tmp)
{
  //bool test1 = false, test2 = false;
  set<Element> set1, set2;
  set1 = this -> getCollection();
  set2 = tmp.getCollection();
  
  // les collections sont diffï¿½entes si elles n'ont pas le mï¿½e nombre d'ï¿½ï¿½ents
  if (set1.size() != set2.size())
    return (true);
    
  /*
  test1 = includes(set1.begin(), set1.end(), set2.begin(), set2.end());
  test2 = includes(set2.begin(), set2.end(), set1.begin(), set1.end());
  if ((!test1) || (!test2))
    return (true);
  else
    return (false);
  */
  
  return(!(set1==set2));
}


// ==============================================================

bool SetOfElements::operator==(SetOfElements tmp)
{
  //bool test1 = false, test2 = false;
  set<Element> set1, set2;
  set1 = this -> getCollection();
  set2 = tmp.getCollection();
  
 
  //test1 = includes(set1.begin(), set1.end(), set2.begin(), set2.end());
  //test2 = includes(set2.begin(), set2.end(), set1.begin(), set1.end());
  //if ((test1) && (test2))
  //  return (true);
  //else
  //  return (false);
  
  return(set1==set2);
}


// ==============================================================

void SetOfElements::setCollection(set<Element> init)
{
  collection = init;
}


// ==============================================================

set<Element> SetOfElements::getCollection() const
{
  return (collection);
}

// ==============================================================

int SetOfElements::getNbElements() const
{
  return collection.size();
}


// ==============================================================

//void SetOfElements::setName(char * init)
void SetOfElements::setName(string init)
{
  name = init;
}


// ==============================================================

string SetOfElements::getName() const
{
  return (this -> name);
}


// ==============================================================

void SetOfElements::setTable(string init)
{
  table = init;
}


// ==============================================================

string SetOfElements::getTable() const
{
  return (this -> table);
}


// ==============================================================

SetOfElements SetOfElements::unionSets(SetOfElements tmp)
{
  SetOfElements res; 
  set<Element> tmpSoE1, tmpSoE2;
  set<Element>::iterator itSoE1, itSoE2;
  
  tmpSoE1.clear();
  tmpSoE1 = this -> getCollection();
  tmpSoE2.clear();
  tmpSoE2 = tmp.getCollection();
  
  res.clear();
  
  // union de deux SetOfElements 
  // en prenant en compte les elementSet plutot que les number
  
  // on parcourt le premier ensemble et on ajoute l'element que si le
  // SetOfElements ne contient pas deja un element ayant le meme elementSet
  for (itSoE1 = tmpSoE1.begin() ; itSoE1 != tmpSoE1.end() ; itSoE1++)
  {
    if (res.getNumberBySet(itSoE1 -> getItemSet()) == -1)
      res.add(*itSoE1);
  }
  
  // on fait de meme avec le deuxieme ensemble
  for (itSoE2 = tmpSoE2.begin() ; itSoE2 != tmpSoE2.end() ; itSoE2++)
  {
    if (res.getNumberBySet(itSoE2 -> getItemSet()) == -1)
      res.add(*itSoE2);
  }
  
  // on retourne l'ensemble obtenu
  return (res);
}


// ==============================================================

SetOfElements SetOfElements::SoE_union(SetOfElements tmp)
{
  SetOfElements tmpUnion;
  set<Element> ens1, ens2, ensUnion;
  set<Element>::iterator it;
  insert_iterator<set<Element, less<Element> > > ii (ensUnion, ensUnion.begin());

   ens1 = this -> getCollection();
  ens2 = tmp.getCollection();

  // utilisation de la fonction "set_union" de la STL pour les set
  set_union(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), ii);

  for (it = ensUnion.begin() ; it != ensUnion.end() ; it++)
    tmpUnion.add(*it);

  return (tmpUnion);
}


// ==============================================================

SetOfElements SetOfElements::SoE_minus(SetOfElements tmp)
{
  SetOfElements tmpMinus;
  set<Element> ens1, ens2, ensMinus;
  set<Element>::iterator it;
  insert_iterator<set<Element, less<Element> > > ii (ensMinus, ensMinus.begin());

  ens1 = this -> getCollection();
  ens2 = tmp.getCollection();

  // utilisation de la fonction "set_difference" de la STL pour les set
  set_difference(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), ii);

  for (it = ensMinus.begin() ; it!= ensMinus.end() ; it++)
    tmpMinus.add(*it);

  return (tmpMinus);
}


// ==============================================================

void SetOfElements::SoETraiteDebut(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // balise <Collection>
        /*FILE *fp = fopen("output.txt","wb");
        fprintf(fp,"%s --",((char *)xmlTextReaderName(reader)));
        fclose(fp);*/
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Collection")) == 0))
  {
    // le nom du fichier XML_COLLECTION
    xmlChar * attrName = xmlCharStrdup("name");
    xmlChar * tmpName = NULL;
    tmpName = xmlTextReaderGetAttribute(reader, attrName);

    name = (char *)(tmpName);

    // le nombre d'elements
    xmlChar * attrNbElements = xmlCharStrdup("nbElements");
    xmlChar * tmpNbElements = NULL;
    tmpNbElements = xmlTextReaderGetAttribute(reader, attrNbElements);
    
    // le nom du fichier XML_TABLE correspondant
    xmlChar * attrTable = xmlCharStrdup("tableName");
    xmlChar * tmpTableName = NULL;
    tmpTableName = xmlTextReaderGetAttribute(reader, attrTable);

    table = (char *)(tmpTableName);

    // initialisation du mapping
    tmpTable.setName(table);
    tmpTable.rewind();

    etat = SoECollection;
  }
}


// --------------------------------------------------------------


void SetOfElements::SoETraiteCollection(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // balise <Element>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Element")) == 0))
  {
    yaNumber = false;
    yaSet = false;
    etat = SoEElement;
  }

  // balise </Collection>
  if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Collection")) == 0))
    etat = SoEFin;
}


// --------------------------------------------------------------


void SetOfElements::SoETraiteElement(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // balise <Number>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Number")) == 0))
  {
    tmpElement.setNumber(-1);
    etat = SoENumber;
  }

  // balise <Set>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Set")) == 0))
  {
    SetOfInt empty;
    tmpElement.setItemSet(empty);
    etat = SoESet;
  }

  // balise </Element>
  if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Element")) == 0) && (yaNumber) && (yaSet))
  {
    etat = SoECollection;
    add(tmpElement);
  }
}


// --------------------------------------------------------------


void SetOfElements::SoETraiteNumber(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // entre <Number> et </Number>
  if (xmlTextReaderNodeType(reader) == contenuBalise)
  {
    int tmpNumber = atoi((char *)(xmlTextReaderValue(reader)));
    tmpElement.setNumber(tmpNumber);
    yaNumber = true;
    etat = SoEElement;
  }
}


// --------------------------------------------------------------


void SetOfElements::SoETraiteSet(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // balise <Item>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
    etat = SoEItem;

  // balise </Set>
  if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Set")) == 0))
  {
    yaSet = true;
    etat = SoEElement;
  }
}


// --------------------------------------------------------------


void SetOfElements::SoETraiteItem(int & etat, xmlTextReaderPtr & reader, bool & yaNumber, bool & yaSet, Element & tmpElement, Table & tmpTable)
{
  // entre <Item> et </Item>
  if (xmlTextReaderNodeType(reader) == contenuBalise)
  {
    char * tmpItem = (char *)(xmlTextReaderValue(reader));
    int tmp = tmpTable.getItemByName(tmpItem);
    SetOfInt tmpSet = tmpElement.getItemSet();
    tmpSet.insert(tmp);
    tmpElement.setItemSet(tmpSet);
    etat = SoESet;
  }
}


// --------------------------------------------------------------

void SetOfElements::load()
{
  //char * filename = getName();

/* Ici il y a un bug. Quand on passe filename a fic.open, filename est modifié, ce qui empeche XML de l'ouvrir.
        De plsu ce test est inutil puisqu'il suffit de tester la bonne ouverture du fichier par XML
  ifstream fic;
  fic.open(filename);

  if (fic != NULL)
  { */
    // initialistion d'un xmlReader
    xmlTextReaderPtr reader = NULL;
        reader = xmlNewTextReaderFilename(getName().c_str());
    if (reader != NULL) {
            
        // on fait un rewind sur tmpTable pour initialiser le mapping
    Table tmpTable;       

    Element tmpElement;

    int ret = 1;
    int etat = SoEDebut;

    bool yaNumber = false;
    bool yaSet = false;

    while ((ret == 1) && (etat != SoEFin))
    {
      // on avance dans la lecture du fichier
      ret = xmlTextReaderRead(reader);

      switch (etat)
      {
        case SoEDebut : SoETraiteDebut(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
        case SoECollection : SoETraiteCollection(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
        case SoEElement : SoETraiteElement(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
        case SoENumber : SoETraiteNumber(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
        case SoESet : SoETraiteSet(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
        case SoEItem : SoETraiteItem(etat, reader, yaNumber, yaSet, tmpElement, tmpTable); break;
      }
    }
  }
}


// ==============================================================

void SetOfElements::save()
{
  if ((name != "") && (table != ""))
  {
      
    ofstream fic;
    fic.open(getName().c_str());
    if (fic != NULL)
    {
      // en tete du fichier
      fic << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
      fic << "<!DOCTYPE racine SYSTEM \"collection.dtd\">" << endl;
      fic << endl;

      fic << "<" << baliseCollection << " name=\"" << name << "\" nbElements=\"" << getNbElements() << "\" tableName=\"" << table << "\">" << endl;
   
      // Ecriture de chaque element
      SoE_iterator itSoE;
      int tmpNumber;
      SetOfInt tmpItemSet;
      set<int> tmpSet;
      set<int>::iterator itSet;
      //char * itemName;
      string itemName;
           
      // on a besoin du mapping de la Table associee
      Table tmpTable;
      
      tmpTable.setName(table);
      tmpTable.rewind();
      
      for (itSoE = begin() ; itSoE != end() ; itSoE++)
      {
        fic << "<" << baliseElement << ">" << endl;

        // le numero de l'element
        tmpNumber = itSoE -> getNumber();
        fic << "<" << baliseNumber << ">";
        fic << tmpNumber;
        fic << "</" << baliseNumber << ">" << endl;

        // l'ensemble associeï¿½a cet element
        tmpItemSet = itSoE -> getItemSet();
 
        // on veut maintenant avoir acces a chaque element de ItemSet
        tmpSet = tmpItemSet;
        fic << "<" << baliseSet << ">" << endl;
        for (itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++)
        {
          itemName = tmpTable.getNameOfItem(*itSet);
          fic << "<" << baliseItem << ">";
          fic << itemName;
          fic << "</" << baliseItem << ">" << endl;
        }
        fic << "</" << baliseSet << ">" << endl;

        fic << "</" << baliseElement << ">" << endl;
      }
     
      fic << "</" << baliseCollection << ">" << endl;
      
      // et le fichier XML
      fic.close();
    }
  }
}


// ==============================================================

void SetOfElements::add(Element eltToAdd)
{
  
  //printf("Insertion de   ");
  //eltToAdd.affiche();
  // on doit inserer l'element dans la collection
  collection.insert(eltToAdd);
}


// ==============================================================

void SetOfElements::remove(Element eltToRemove)
{
  // on n'enleve l'element que si il existe
  if (collection.count(eltToRemove) != 0)
  {
    // on doit supprimer l'element de la collection
    collection.erase(eltToRemove);
  }
}


// ==============================================================

int SetOfElements::getNumberBySet(SetOfInt ens)
{
  // on doit comparer les itemset dans elementSet set<Element>
  SoE_iterator itEltSet;
  SetOfInt tmpItemSet;
  int tmpNumber;

  // pour chaque element de la collection
  for (itEltSet = begin() ; itEltSet != end() ; itEltSet++)
  {
    tmpItemSet = itEltSet -> getItemSet();
    // on compare l'elementSet de l'element de l'ensemble 
    // avec l'SetOfInt passe en parametre
    if (tmpItemSet == ens)
    {
      tmpNumber = itEltSet -> getNumber();
      // si c'est le meme on retourne le number de l'element courant
      return (tmpNumber);
    }
  }

  // sinon on retourne -1
  return (-1);
}


// ==============================================================


SetOfInt SetOfElements::getSetByNumber(int nb)
{
  // on doit cherchï¿½le int dans l'ensemble
  SoE_iterator itEltSet;
  SetOfInt tmpItemSet;
  int tmpNumber;
  
  tmpItemSet.clear();

  // pour chaque element de la collection
  for (itEltSet = begin() ; itEltSet != end() ; itEltSet++)
  {
    tmpNumber = itEltSet -> getNumber();
    // on compare le number de l'element de l'ensemble
    // avec l'entier passe en parametre
    if (tmpNumber == nb)
    {
      // si c'est le meme on affecte un SetOfInt
      tmpItemSet = itEltSet -> getItemSet();
    }
  }
  
  // on retourne l'SetOfInt
  // si le numero a ete trouve celui ci aura ete affecte
  // sinon on renvoie l'ensemble vide par defaut
  return (tmpItemSet);
}


// ==============================================================

SetOfInt SetOfElements::getNumbers()
{
  // renvoie un ensemble d'entiers correspondant aï¿½la liste
  // des numbers des elements
  SoE_iterator itEltSet;
  int tmpNumber;
  SetOfInt tmp;

  // pour chaque element de la collection
  for (itEltSet = begin() ; itEltSet != end() ; itEltSet++)
  {
    // on insere le numero de l'element dans un SetOfInt
    tmpNumber = itEltSet -> getNumber();
    tmp.insert(tmpNumber);
  }
  
  // on retourne cet SetOfInt
  return (tmp);
}

// ==============================================================

int SetOfElements::getNextAvailableNumber() {
  if (getSize())
    return (getCollection().rbegin())->getNumber() + 1;
  else
    return 0;
}


// ==============================================================

int SetOfElements::getSize()
{
  // utilisation de la fonction "size" de la STL sur les set
  return (collection.size());
}


// ==============================================================

 void SetOfElements::closureAll(string nameTable)
{
  Table tmpTable;
  tmpTable.setName(nameTable);
  tmpTable.rewind(); // utilise la fonction readHeader()
  
  SoE_iterator itEltSet;
  SetOfInt tmpSetOfInt;
  SetOfInt tmpEmptySet;
  
  tmpSetOfInt = tmpTable.getListItems();
  tmpEmptySet.clear();
  

  // Pour chaque element faire
  // on initialise l'ensemble à l'ensemble des elements
  for (itEltSet = begin() ; itEltSet != end() ; itEltSet++)
  {
    if (itEltSet -> getItemSet() != tmpSetOfInt)
    {
      itEltSet -> setItemSet(tmpEmptySet);
      itEltSet -> setItemSet(tmpSetOfInt);
    }
  }

  // Pour chaque tuple T de Table faire
  // On doit lire dans le fichier XML avec la fonction readTuple()
  int nbTuples = tmpTable.getNbTuples();
  SetOfInt tmpTuple;
  int numero;
  set<int>::iterator test;
  set<int>::iterator it;
  SetOfInt newItemSet;
  set<int> ens1, ens2, ensInter;
  insert_iterator<set<int, less<int> > > ii (ensInter, ensInter.begin());
  

  for (int i = 0 ; i < nbTuples ; i++)
  {
    tmpTuple = tmpTable.readTuple();

    // Pour chaque element faire
    for (itEltSet = collection.begin() ; itEltSet != collection.end() ; itEltSet++)
    {
      numero = itEltSet -> getNumber();

      // .getNumber() appartient a T
      if (tmpTuple.find(numero) != tmpTuple.end())
      {
        // element.getItemSet() inter T = SetOfInt
        ens1 = itEltSet -> getItemSet();
        ens2 = tmpTuple;

        // utilisation de la fonction "set_intersection" de la STL pour les set
        set_intersection(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), ii);

        for (it = ensInter.begin() ; it != ensInter.end() ; it++)
          newItemSet.insert(*it);
        itEltSet -> setItemSet(newItemSet);

        ensInter.clear();
      }
      newItemSet.clear();
    }
    tmpTuple.clear();
  }
}

// =============================================================

SetOfElements SetOfElements::elementToSetOfElements(Element el) {
  SetOfElements out;
  out.setName(getName());
  out.setTable(getTable());
  for(set<Element>::iterator it = begin();
      it != end(); ++it) {
    //Si l'element du SoE est dans l'element passe en paramètre
    //it->getItemSet().affiche();
    //cout << " inclus dans ";
    //el.getItemSet().affiche();
    if (el.getItemSet().I_includes(it->getItemSet())) {
      //cout << "oui" << endl;
      //On le rajoute au SoE final
      out.add(*it);
    }
  }
  return out;
}

// =============================================================

SetOfElements::SoE_iterator SetOfElements::find(const Element & tmp) {
  for(SoE_iterator it = begin(); it != end(); ++it) {
    if (it->getItemSet() == tmp.getItemSet()) return it;
  }
  return end();
}

// ==============================================================

void SetOfElements::affiche2()
{
  cout << "nombre d'elements : " << getNbElements() << endl;

  if (name != "")
    cout << "nom du fichier XML_COLLECTION : " << name << endl;
  if (table != "")
    cout << "nom du fichier XML_TABLE : " << table << endl;

  // utilise la fonction affiche() du TDA Element
  SoE_iterator itSet;
  Table tbl;
  tbl.setName(table);
	tbl.rewind();
  
  for (itSet = begin() ; itSet != end() ; itSet++)
  {
    cout << itSet->getNumber() << " = " << tbl.getNameOfSetOfInt(itSet->getItemSet()) << endl;
  }
}

void SetOfElements::affiche()
{
  cout << "nombre d'elements : " << getNbElements() << endl;

  if (name != "")
    cout << "nom du fichier XML_COLLECTION : " << name << endl;
  if (table != "")
    cout << "nom du fichier XML_TABLE : " << table << endl;

  // utilise la fonction affiche() du TDA Element
  SoE_iterator itSet;

  for (itSet = begin() ; itSet != end() ; itSet++)
  {
    itSet -> affiche();
  }
}

