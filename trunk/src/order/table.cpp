/********************************************************/
/* Application : Fouille de donnees      */
/* Nom du fichier : table.hpp        */
/* Derniere mise a jour : 16/10/2005      */
/* Auteur : Noyer Caroline, Olivier COUPELON        */
/********************************************************/


#include "table.hpp"

#define baliseTable "Table"
#define baliseListItems "ListItems"
#define baliseItem "Item"
#define baliseTuple "Tuple"

#define baliseOuvrante 1
#define contenuBalise 3
#define baliseFermante 15
#define baliseVide 14

#define ICDebut 0
#define ICListItems 1
#define ICItem 2
#define ICFin 3

#define RTDebut 0
#define RTTuple 1
#define RTItem 2
#define RTFin 3



// ==============================================================

Table::Table()
{
  name = "";
  nbTuples = 0;
  nbItems = 0;
  mapping.clear();
  currentTuple = 0;
}


// ==============================================================

Table::Table(const Table & tmp)
{
  name = tmp.name;
  nbTuples = tmp.nbTuples;
  nbItems = tmp.nbItems;
  mapping = tmp.mapping;
  currentTuple = tmp.currentTuple;
}


// ==============================================================

Table::~Table()
{
}


// ==============================================================

void Table::clear()
{
  name = "";
  nbTuples = 0;
  nbItems = 0;
  mapping.clear();
  currentTuple = 0;
}


// ==============================================================

//void Table::setName(char * initName)
void Table::setName(string initName)
{
  name = initName;
}


// ==============================================================

//char * Table::getName() const
string Table::getName() const
{
  return (name);
}


// ==============================================================

void Table::setNbTuples(int initNbTuples)
{
  nbTuples = initNbTuples;
}


// ==============================================================

int Table::getNbTuples() const
{
  return (nbTuples);
}


// ==============================================================

void Table::setNbItems(int initNbItems)
{
  nbItems = initNbItems;
}


// ==============================================================

int Table::getNbItems() const
{
  return (nbItems);
}


// ==============================================================

void Table::setMapping(map<string,int> tmp)
{
  mapping=tmp;
}


// ==============================================================

map<string,int> Table::getMapping() const
{
  return (mapping);
}


// ==============================================================

void Table::setXmlReader(xmlTextReaderPtr initReader)
{
  xmlReader = initReader;
}


// ==============================================================

xmlTextReaderPtr Table::getXmlReader() const
{
  return (xmlReader);
}


// ==============================================================

void Table::setCurrentTuple(int initCurrentTuple)
{
  currentTuple = initCurrentTuple;
}


// ==============================================================

int Table::getCurrentTuple() const
{
  return (currentTuple);
}


// ==============================================================

bool Table::rewind()
{
  xmlTextReaderPtr reader = NULL;

  if ( (reader = xmlNewTextReaderFilename(getName().c_str())) == NULL)
  {
    cout<<endl<<"Essai d'ouvrir "<< getName() <<endl;
    cout << "erreur fatale " << endl;
    return (false);
  }
  xmlTextReaderRead(reader);

  // initialisation du xmlReader
  setXmlReader(reader);

  // Utilise readHeader()
  readHeader();

  // le tuple courant est 0
  currentTuple = 0;

  return (true);
}


// ==============================================================

void Table::readHeader()
{
  xmlTextReaderPtr reader = getXmlReader();
  int ret;

  if (reader != NULL)
  {
    // on avance le reader pour la lecture
    ret = xmlTextReaderRead(reader);
    if (ret == 1)
    {
      // on recupere les differents attributs

      // le nombre d'items dans la relation
      xmlChar * attrNbItems = xmlCharStrdup("nbItems");
      xmlChar * tmpNbItems = NULL;
      tmpNbItems = xmlTextReaderGetAttribute(reader, attrNbItems);
      
      // le nom de la table
      xmlChar * attrName = xmlCharStrdup("name");
      xmlChar * tmpName = NULL;
      tmpName = xmlTextReaderGetAttribute(reader, attrName);

      // le nombre de tuples dans la relation
      xmlChar * attrNbTuples = xmlCharStrdup("nbTuples");
      xmlChar * tmpNbTuples = NULL;
      tmpNbTuples = xmlTextReaderGetAttribute(reader, attrNbTuples);


      // initialisation des attributs du TDA
      name = (char *)(tmpName);
      nbTuples = atoi((char *)(tmpNbTuples));
      nbItems = atoi((char *)(tmpNbItems));
    }
  }

  // on r�initialise le reader
  setXmlReader(reader);

  // Utilise initCorrespond
  initCorrespond();
}


// ==============================================================

/*void Table::close()
{
  // ferme juste le fichier Table
  (this -> fic).close();
}*/


// ==============================================================

void Table::ICTraiteDebut(int & etat, int & cpt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  // il faut que la balise soit <ListItems>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("ListItems")) == 0))
    etat = ICListItems;

  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

void Table::ICTraiteListItems(int & etat, int & cpt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  // balise = <Item>
  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
    etat = ICItem;

  if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("ListItems")) == 0))
    etat = ICFin;

  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

void Table::ICTraiteItem(int & etat, int & cpt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  // on doit recuperer le contenu de la balise Item
  if (xmlTextReaderNodeType(reader) == contenuBalise)
  {
    //char * tmpValue = (char *)(xmlTextReaderValue(reader));
    string tmpValue = (char *)(xmlTextReaderValue(reader));
    mapping[tmpValue] = cpt;
    cpt++;
    etat = ICListItems;
  }

  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

void Table::initCorrespond()
{
  // initialisation de la liste d'items
  // -----------------------------------------------------
  // compris entre les balises <ListItems> et </ListItems>

  xmlTextReaderPtr reader;
  int ret = 1;
  int nbItemsInMapping = 0;
  int etat = ICDebut;

  while ((etat != ICFin) && (ret == 1))
  {
    // on recupere le reader
    reader = getXmlReader();
    // on l'avance dans la lecture
    ret = xmlTextReaderRead(reader);
    // on le repositionne
    setXmlReader(reader);

    switch (etat)
    {
      case ICDebut : ICTraiteDebut(etat,nbItemsInMapping); break;
      case ICListItems : ICTraiteListItems(etat,nbItemsInMapping); break;
      case ICItem : ICTraiteItem(etat,nbItemsInMapping); break;
    }
  }

  // on réinitialise le reader
  setXmlReader(reader);
}


// ==============================================================

void Table::RTTraiteDebut(int & etat, SetOfInt & tmpSetOfInt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Tuple")) == 0))
    etat = RTTuple;
    
  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

void Table::RTTraiteTuple(int & etat, SetOfInt & tmpSetOfInt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  if ((xmlTextReaderNodeType(reader) == baliseOuvrante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Item")) == 0))
    etat = RTItem;

  if ((xmlTextReaderNodeType(reader) == baliseFermante) && (xmlStrcmp(xmlTextReaderName(reader), xmlCharStrdup("Tuple")) == 0))
    etat = RTFin;

  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

void Table::RTTraiteItem(int & etat, SetOfInt & tmpSetOfInt)
{
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();

  // on doit r�up�er le contenu de la balise Item
  if (xmlTextReaderNodeType(reader) == contenuBalise)
  {
    //char * tmpValue = (char *)(xmlTextReaderValue(reader));
    string tmpValue = (char *)(xmlTextReaderValue(reader));
    int eltToInsert = getItemByName(tmpValue);
    tmpSetOfInt.insert(eltToInsert);
    etat = RTTuple;
  }

  // on réinitialise le reader
  setXmlReader(reader);
}

// ---------------------------------------------------------------

SetOfInt Table::readTuple()
{
  SetOfInt tmp;
  // on recupere le reader
  xmlTextReaderPtr reader = getXmlReader();
  int etat;
  int ret = 1;

  // si c'est le dernier tuple alors on est a la fin => pas de traitement
  if (currentTuple == nbTuples)
    etat = RTFin;

  etat = RTDebut;

  while ((etat != RTFin) && (ret == 1))
  {
    // on recupere le reader
    reader = getXmlReader();
    // on l'avance pour la lecture
    ret = xmlTextReaderRead(reader);
    
    // on le repositionne
    setXmlReader(reader);

    switch (etat)
    {
      case RTDebut : RTTraiteDebut(etat, tmp); break;
      case RTTuple : RTTraiteTuple(etat, tmp); break;
      case RTItem : RTTraiteItem(etat, tmp); break;
    }
  }

  // on reinitialise le reader
  setXmlReader(reader);
  // on passe au tuple suivant
  currentTuple++;

  return (tmp);
}


// ==============================================================

void Table::writeHeader()
{
  //char * filename = getName();
  string filename = getName();
  
  if (filename != "")
  {
    ofstream fic;
    // ouverture du fichier XML
    //fic.open(filename);
    fic.open(filename.c_str());
    
    if (fic != NULL)
    {
      fic << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
      fic << "<!DOCTYPE ruletree SYSTEM \"table.dtd\">" << endl;
      fic << endl;

      // on ecrit a present l'element racine
      //fic << "<" << baliseTable << " name=\"" << name << "\" nbTuples=\"" << nbTuples << "\" nbItems=\"" << nbItems << "\">" << endl;
        
        fic << "<" << baliseTable << " nbItems=\"" << nbItems << "\" name=\"" << name << "\" nbTuples=\"" << nbTuples <<  "\">" << endl;
      
      // on doit a present ecrire la liste des items
      fic << "<" << baliseListItems << ">" << endl;
      //map<char *,int>::iterator itMap;
      map<string,int>::iterator itMap;
      for (itMap = mapping.begin() ; itMap != mapping.end() ; itMap++)
      {
        fic << "<" << baliseItem << ">";
        fic << itMap -> first;
        fic << "</" << baliseItem << ">";
        fic << endl;
      }
      fic << "</" << baliseListItems << ">" << endl;
    }
    else
    {
      cout << "Erreur dans la creation du fichier !!!" << endl;
    }
    fic.close();
  }
}


// ==============================================================

void Table::writeTuple(SetOfInt ens)
{
  //char * filename = getName();
  string filename = getName();
  
  if (filename != "")
  {
    ofstream fic;
    // on ouvre le fichier : app => se place a la fin de ce qui est deja ecrit
    //fic.open(filename, ios::app);
    fic.open(filename.c_str(), ios::app);
    if (fic == NULL)
    {
      cout << "ben c po ouvert" << endl;
    }
    fic << "<" << baliseTuple << ">" << endl;

    set<int> tmp = ens;
    set<int>::iterator itSet;
    //char * tmpItem;
    string tmpItem;
    
    // on doit �rire le NOM correspondant au num�o => mapping
    // pour cela on utilise la fonction getNameOfItem
    for (itSet = tmp.begin() ; itSet != tmp.end() ; itSet++)
    {
      tmpItem = getNameOfItem(*itSet);
      fic << "<" << baliseItem << ">" << tmpItem << "</" << baliseItem << ">" << endl;
    }

    fic << "</" << baliseTuple << ">" << endl;
    fic.close();
  }
}


// ==============================================================

void Table::writeEnd()
{
  //char * filename = getName();
  string filename = getName();
  
  if (filename != "")
  {
    ofstream fic;
    //fic.open(filename, ios::app);
    fic.open(filename.c_str(), ios::app);
    if (fic == NULL)
    {
      cout << "ben c po ouvert" << endl;
    }

    fic << "</" << baliseTable << ">" << endl;
    fic.close();
  }
}


// ==============================================================

SetOfInt Table::getListItems()
{
  SetOfInt tmpSetOfInt;
  //map<char *,int> tmpMapping = mapping;
  //map<char *,int>::iterator itMap;
  
  map<string,int> tmpMapping = mapping;
  map<string,int>::iterator itMap;
  
  tmpSetOfInt.clear();

  // pour avoir la liste des items il suffit de parcourir le mapping 
  // et de mettre dans un SetOfInt tous les numeros
  for (itMap = tmpMapping.begin() ; itMap != tmpMapping.end() ; itMap++)
  {
    tmpSetOfInt.insert(itMap -> second);
  }

  // on retourne donc cet ensemble
  // rq : si rien n'a ete ajoute l'ensemble vide sera renvoye
  return (tmpSetOfInt);
}


// ==============================================================

//int Table::getItemByName(char * itemName)
int Table::getItemByName(string itemName)
{
  //map<char *, int> tmpMapping;
  //map<char *, int>::iterator itMap;
  map<string, int> tmpMapping;
  map<string, int>::iterator itMap;
  
  int test;
  int intElement;
  tmpMapping = mapping;

  // on parcourt chaque element du mapping
  for (itMap = tmpMapping.begin() ; itMap != tmpMapping.end() ; itMap++)
  {
    intElement =0;
    test = -1;

    // on compare itemName avec le char * de l'element
    //test = strcmp(itMap -> first, itemName);
    test = (itMap -> first == itemName);
    //if (test == 0)
    if(test)
    {
      // si c'est le meme on retourne l'entier correspondant
      intElement = itMap -> second;
      return (intElement);
    }
  }
  
  // retourne -1 si l'item n'a pas ete trouve
  return (-1);
}


// ==============================================================

void Table::setItemName(int itemNumber, string itemName)
{
  mapping[itemName] = itemNumber;
}


// ==============================================================

string Table::getNameOfItem(int itemNumber)
{
  map<string, int> tmpMapping;
  map<string, int>::iterator itMap;
  
  string charElement;
  tmpMapping = mapping;

  // on parcourt les elements du mapping
  for (itMap = tmpMapping.begin() ; itMap != tmpMapping.end() ; itMap++)
  {
    charElement="";
    // si le numero passe en parametre est le meme que celui de l'element du mapping
    if (itMap -> second == itemNumber)
    {
      charElement = itMap -> first;
      
      // on retourne la chaine associee
      return (charElement);
    }
  }
  
  // sinon (rien n'a ete trouve) on retourne la chaine vide
  return ("");
}


// ==============================================================

void Table::affiche()
{
  // on affiche les diff�ents attributs
  cout << "Nom de la table : " << endl;
  cout << "\t" << name << endl;
  cout << "Nombre de tuples : " << endl;
  cout << "\t" << nbTuples << endl;
  cout << "Nombre d'items : " << endl;
  cout << "\t" << nbItems << endl;

  cout << "Mapping : " << endl;
  //map<char *,int>::iterator itMap;
  map<string,int>::iterator itMap;
  for (itMap = mapping.begin() ; itMap != mapping.end() ; itMap++)
  {
    cout << "\t" << itMap -> first << " => " << itMap -> second << endl;
  }
}

// ==============================================================
// ==============================================================
// ==============================================================

void Table::affMapping()
{
  map<string,int>::iterator it;
   
  for(it=mapping.begin();it!=mapping.end();++it)
  {
    cout<<it->first<<" -> "<<it->second<<endl;
  }
  cout<<endl;
}

