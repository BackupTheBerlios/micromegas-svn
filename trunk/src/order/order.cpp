/********************************************************/
/* Application : Fouille de donnees                     */
/* Nom du fichier : order.cpp                           */
/* Derniere mise a jour : 23/07/2004                    */
/* Auteur : Noyer Caroline                              */
/********************************************************/


#include "order.hpp"


// ==============================================================

Order::Order()
{
  J.clear();
  imPred.clear();
  imSucc.clear();
}


// ==============================================================

Order::Order(const Order & init)
{
  J = init.J;
  imPred = init.imPred;
  imSucc = init.imSucc;
}


// ==============================================================

Order::~Order()
{

}


// ==============================================================
void Order::clear()
{
  J.clear();
  imPred.clear();
  imSucc.clear();
}


// ==============================================================

void Order::setJ(SetOfElements init)
{
  //On commence par reinitialiser l'odre
  clear();
  
  set<Element>::iterator itSet;
  set<Element> tmpCollection;
  
  J.setName(init.getName());
  J.setTable(init.getTable());
  
  // pour chaque element de ce SetOfElements
  tmpCollection = init.getCollection();
  for (itSet = tmpCollection.begin() ; itSet != tmpCollection.end() ; itSet++)
  {
    // on l'insere dans l'ordre
    insert(*itSet);
  }
}


// ==============================================================

SetOfElements Order::getJ() const
{
  return (J);
}


// ==============================================================

void Order::setImPred(Element N, SetOfElements init)
{
  imPred[N.getNumber()].clear();
  imPred[N.getNumber()] = init;
}


// ==============================================================

SetOfElements Order::getImPred(Element tmp)
{
  SetOfElements tmpSetOfElements;
  int number = tmp.getNumber();
  
  tmpSetOfElements.clear();

  map<int, SetOfElements>::iterator itMap;
  // on parcourt chaque predecesseur
  for (itMap = imPred.begin() ; itMap != imPred.end() ; itMap++)
  {
    if (itMap -> first == number)
      return (itMap -> second);
  }

  // si on ne trouve pas, on renvoie un ensemble vide
  return (tmpSetOfElements);
}


// ==============================================================

void Order::setImSucc(Element N, SetOfElements init)
{
  imSucc[N.getNumber()].clear();
  imSucc[N.getNumber()] = init;
}


// ==============================================================

SetOfElements Order::getImSucc(Element tmp)
{
  SetOfElements tmpSetOfElements;
  int number = tmp.getNumber();

  map<int, SetOfElements>::iterator itMap;
  // on parcourt chaque successeur
  for (itMap = imSucc.begin() ; itMap != imSucc.end() ; itMap++)
  {
    if (itMap -> first == number)
      return (itMap -> second);
  }

  // si on ne trouve pas, on renvoie un ensemble vide
  return (tmpSetOfElements);
}


// ==============================================================

void Order::setName(string init)
{
  J.setName(init);
}


// ==============================================================

string Order::getName()
{
  return (J.getName());
}


// ==============================================================

void Order::setTable(string init)
{
  J.setTable(init);
}


// ==============================================================

string Order::getTable()
{
  return (J.getTable());
}


// ==============================================================

void Order::load()
{
  string filename = getName();
  
  // initialisation d'un SetOfElments
  SetOfElements tmpSetOfElements;
  // nom du fichier contenant la collection
  tmpSetOfElements.setName(filename);
  // nom du fichier de la table correspondante
  tmpSetOfElements.setTable(getTable());
  // chargement de la collection
  tmpSetOfElements.load();

  set<Element>::iterator itSet;
  set<Element> tmpCollection;

  // pour chaque element de ce SetOfElements
  tmpCollection = tmpSetOfElements.getCollection();
  for (itSet = tmpCollection.begin() ; itSet != tmpCollection.end() ; itSet++)
  {
    // on l'insere dans l'ordre
    insert(*itSet);
  }
}


// ==============================================================

void Order::save()
{
  // sauvegarder l'ordre revient a sauvegarder la collection
  J.save();
}


// ==============================================================

SetOfInt Order::getJnumbers()
{
  // on veut l'ensemble des numeros de J
  return (J.getNumbers());
}


// ==============================================================

void Order::insert(Element N)
{
  SetOfElements tmp;
  set<Element> tmpCollection = J.getCollection(), tmpImPred, tmpImSucc;
  set<Element>::iterator itM, itIP, itIS;
  set<int> setM, setN, setMbis;
  int arc;
  bool test = false;
  
  setN = (N.getItemSet());
    
  // Pour chaque element M de J.collection
  for (itM = tmpCollection.begin() ; itM != tmpCollection.end() ; itM++)
  {
    arc = 0;
    setM = (itM -> getItemSet());
    test = includes(setM.begin(), setM.end(), setN.begin(), setN.end());

    // Si N INCLUS DANS M
    if (test)
    {
      // Pour M' imPred(M)
      tmpImPred = (getImPred(*itM)).getCollection();
      for (itIP = tmpImPred.begin() ; itIP != tmpImPred.end() ; itIP++)
      {
        setMbis = (itIP -> getItemSet());
        test = includes(setMbis.begin(), setMbis.end(), setN.begin(), setN.end());
        // si N INCLUS DANS M'
        if (test)
        {
          arc = 1;
        }
      }

      // Si arc != 1
      if (arc != 1)
      {
        // ImSucc(N) U M
        tmp.clear();
        tmp = getImSucc(N);
        tmp.add(*itM);
        imSucc[N.getNumber()] = tmp;
        
        for (itIP = tmpImPred.begin() ; itIP != tmpImPred.end() ; itIP++)
        {
          setMbis = (itIP -> getItemSet());
          test = includes(setN.begin(), setN.end(), setMbis.begin(), setMbis.end());
          if (test)
          {
            // ImPred(M) \ M'
            tmp.clear();
            tmp = getImPred(*itM);
            tmp.remove(*itIP);
            imPred[itM -> getNumber()] = tmp;
          }
        }
        // N ImPred de M
        tmp.clear();
        tmp = getImPred(*itM);
        tmp.add(N);
        imPred[itM -> getNumber()] = tmp;
      }
    }

    test = includes(setN.begin(), setN.end(), setM.begin(), setM.end());
    if(test)
    {
      tmpImSucc = (getImSucc(*itM)).getCollection();
      for (itIS = tmpImSucc.begin() ; itIS != tmpImSucc.end() ; itIS++)
      {
        setMbis = (itIS -> getItemSet());
        test = includes(setN.begin(), setN.end(), setMbis.begin(), setMbis.end());

        // si M' INCLUS N
        if (test)
        {
          arc = 1;
        }
      }

      if (arc != 1)
      {
        // M ImPred de N
        tmp.clear();
        tmp = getImPred(N);
        tmp.add(*itM);
        imPred[N.getNumber()] = tmp;
        
        for (itIS = tmpImSucc.begin() ; itIS != tmpImSucc.end() ; itIS++)
        {
          setMbis = (itIS -> getItemSet());
          test = includes(setMbis.begin(), setMbis.end(), setN.begin(), setN.end());
          if (test)
          {
            // ImSucc(M) \ M'
            tmp.clear();
            tmp = getImSucc(*itM);
            tmp.remove(*itIS);
            imSucc[itM -> getNumber()] = tmp;
          }
        }
        // N ImSucc de M
        tmp.clear();
        tmp = getImSucc(*itM);
        tmp.add(N);
        imSucc[itM -> getNumber()] = tmp;
      }
    }
  }

  // on insere l'element dans la collection
  J.add(N);
}


// ==============================================================

void Order::remove(Element N)
{
  // tmp l'element a supprimer
  set<Element> ImSuccN = getImSucc(N).getCollection();
  set<Element> ImPredN = getImPred(N).getCollection();
  set<Element> tmpSetElement;
  set<Element>::iterator itSetIS, itSetIP, itSet;
  SetOfElements tmpSetOfElements;
  set<int> setIS, setIP, tmpSet;
  int arc;

  // on enleve tmp des predecesseurs des autres elements
  for (itSetIS = ImSuccN.begin() ; itSetIS != ImSuccN.end() ; itSetIS++)
  {
    tmpSetOfElements.clear();
    tmpSetOfElements = getImPred(*itSetIS);
    tmpSetOfElements.remove(N);
    setImPred(*itSetIS, tmpSetOfElements);
  }

  // on enleve tmp des successeurs des autres elements
  for (itSetIP = ImPredN.begin() ; itSetIP != ImPredN.end() ; itSetIP++)
  {
    tmpSetOfElements.clear();
    tmpSetOfElements = getImSucc(*itSetIP);
    tmpSetOfElements.remove(N);
    setImSucc(*itSetIP, tmpSetOfElements);
  }

  // on recherche les arcs de transitivite eventuellement manquants
  // Pour chaque K de ImSucc
  for (itSetIS = ImSuccN.begin() ; itSetIS != ImSuccN.end() ; itSetIS++)
  {
    // Pour chaque I de ImPred
    for (itSetIP = ImPredN.begin() ; itSetIP != ImPredN.end() ; itSetIP++)
    {
      // Si I.getItemSet() INCLUS DANS K.getItemSet()
      setIS.clear();
      setIS = (itSetIS -> getItemSet());
      setIP.clear();
      setIP = (itSetIP -> getItemSet());

      if (includes(setIS.begin(), setIS.end(), setIP.begin(), setIP.end()))
      {
        // I imPred potentiel de K
        arc = 0;

        // Pour chaque L de imPred(K)
        tmpSetElement.clear();
        tmpSetElement = (getImPred(*itSetIS)).getCollection();
        for (itSet = tmpSetElement.begin() ; itSet != tmpSetElement.end() ; itSet++)
        {
          tmpSet.clear();
          tmpSet = (itSet -> getItemSet());
          if (includes(tmpSet.begin(), tmpSet.end(), setIP.begin(), setIP.end()))
          {
            // arc de transitivite�existant
            arc = 1;
          }
        }

        if (arc == 0)
        {
          // pas d'arc de transitivite
          // on ajoute I aux predecesseurs de K
          tmpSetOfElements.clear();
          tmpSetOfElements = getImPred(*itSetIS);
          tmpSetOfElements.add(*itSetIP);
          setImPred(*itSetIS, tmpSetOfElements);

          // on ajoute K aux successeurs de I
          tmpSetOfElements.clear();
          tmpSetOfElements = getImSucc(*itSetIP);
          tmpSetOfElements.add(*itSetIS);
          setImSucc(*itSetIP, tmpSetOfElements);
        }
      }
    }
  }
  // on retire N de J, ImSucc et ImPred
  imSucc.erase(N.getNumber());
  imPred.erase(N.getNumber());
  J.remove(N);
}


// ==============================================================

SetOfElements Order::max()
{
  SetOfElements tmpMax;
  set<Element>::iterator itSet;
  set<Element> tmpCollection = J.getCollection();
  
  tmpMax.clear();
  
  // pour chaque element de la collection
  for (itSet = tmpCollection.begin() ; itSet != tmpCollection.end() ; itSet++)
  {
    // si cet element n'a pas de successeur
    if((getImSucc(*itSet)).getNbElements() == 0)
    {
      // alors c'est un max, on l'insere dans l'ensemble
      tmpMax.add(*itSet);
    }
  }

  // on retourne l'ensemble obtenu
  return(tmpMax);
}


// ==============================================================

SetOfElements Order::min()
{
  SetOfElements tmpMin;
  set<Element>::iterator itSet;
  set<Element> tmpCollection = J.getCollection();
  
  tmpMin.clear();

  // pour chaque element de la collection
  for (itSet = tmpCollection.begin() ; itSet != tmpCollection.end() ; itSet++)
  {
    // si cet element n'a pas de predecesseur
    if((getImPred(*itSet)).getNbElements() == 0)
    {
      // alors c'est un min, on l'insere dans l'ensemble
      tmpMin.add(*itSet);
    }
  }

  // on retourne l'ensemble obtenu
  return(tmpMin);
}


// ==============================================================

Order Order::duplicate()
{
  Order tmpOrder;

  tmpOrder.J = J;
  tmpOrder.imPred = imPred;
  tmpOrder.imSucc = imSucc;

  return (tmpOrder);
}


// ==============================================================

Order Order::getIdeal(SetOfElements I)
{
  SetOfElements traite, ens, tmp1, tmp2, sauvI, aRetirer;
  set<Element>::iterator it;
  set<Element> tmp;
  Order tmpOrdre;

  traite.clear();
  sauvI = I;
  
  // calcul de l'ideal associe a I
  while (traite != sauvI)
  {
    ens.clear();
    ens = sauvI.SoE_minus(traite);
    traite = ens;
    tmp = ens.getCollection();
    for (it = tmp.begin() ; it != tmp.end() ; it++)
    {
      traite.add(*it);
      tmp1 = getImPred(*it);
      tmp2 = sauvI.SoE_union(tmp1);
      sauvI = tmp2;
    }
  }

  // on copie l'ordre
  tmpOrdre = duplicate();

  // on retire les elements de l'ordre qui ne sont pas dans l'ideal
  ens = getJ();
  aRetirer = ens.SoE_minus(sauvI);
  tmp = aRetirer.getCollection();
  for (it = tmp.begin() ; it != tmp.end() ; it++)
  {
    tmpOrdre.remove(*it);
  }
  
  // on retourne l'ideal obtenu
  return (tmpOrdre);
}


// ==============================================================

Order Order::removeFilter(Element x)
{
  // on veut renvoyer l'ordre \ du filtre de tmp
  SetOfElements traite, ens, tmp1, tmp2, sauvI;
  set<Element>::iterator it;
  set<Element> tmp;
  Order tmpOrdre;
  
  sauvI.clear();
  sauvI.add(x);
  traite.clear();

  // calcul du filtre de x
  while (traite != sauvI)
  {
    ens.clear();
    ens = sauvI.SoE_minus(traite);
    traite = ens;
    tmp = ens.getCollection();
    for (it = tmp.begin() ; it != tmp.end() ; it++)
    {
      traite.add(*it);
      tmp1 = getImSucc(*it);
      tmp2 = sauvI.SoE_union(tmp1);
      sauvI = tmp2;
    }
  }

  // copie de l'ordre
  tmpOrdre = duplicate();

  // on retire le filtre de I a cet ordre
  ens = getJ();
  tmp = sauvI.getCollection();
  for (it = tmp.begin() ; it != tmp.end() ; it++)
  {
    tmpOrdre.remove(*it);
  }

  // on renvoie l'ordre ainsi obtenu
  return (tmpOrdre);
}


// ==============================================================

SetOfElements Order::imSuccIdeal(SetOfElements I)
{
  SetOfElements tmpImSucc;
  Order tmpOrder, tmpIdeal, saveIdeal;
  set<Element>::iterator it;
  set<Element> tmp, tmpMin;
  Element tmpElement;
  SetOfInt tmpSetOfInt;
  int num;

  // il faut que I soit un ideal
  tmpIdeal.clear();
  tmpIdeal = getIdeal(I);

  tmp = (tmpIdeal.getJ()).getCollection();
  tmpOrder = duplicate();
  
  // on retire chaque element de l'ideal de l'ordre
  for (it = tmp.begin() ; it != tmp.end() ; it++)
  {
    tmpOrder.remove(*it);
  }
  
  tmpMin = (tmpOrder.min()).getCollection();
  tmpImSucc.clear();

  // les successeurs immediats sont a present les minimaux de l'ordre obtenu
  // il suffit de creer le SetOfElements
  for (it = tmpMin.begin() ; it != tmpMin.end(); it++)
  {
    saveIdeal = tmpIdeal;
    tmpElement.clear();
    num = it -> getNumber();
    tmpElement.setNumber(num);
    tmpSetOfInt = saveIdeal.getJnumbers();
    tmpSetOfInt.insert(num);
    tmpElement.setItemSet(tmpSetOfInt);
    tmpImSucc.add(tmpElement);
  }

  //tmpImSucc.setName(getName());
  //tmpImSucc.setTable(getTable());
  // on retourne l'ensemble des successeurs immediats
  return (tmpImSucc);
}


// ==============================================================

SetOfElements Order::imPredIdeal(SetOfElements I)
{
  SetOfElements tmpImPred;
  Order tmpOrder, tmpIdeal, saveIdeal;
  set<Element>::iterator it;
  set<Element> tmp, tmpMax;
  Element tmpElement;
  SetOfInt tmpSetOfInt;
  int num;

  // il faut que I soit un ideal
  tmpIdeal = getIdeal(I);

  // on veut les elements maximaux de cet ideal
  tmpMax.clear();
  tmpMax = (tmpIdeal.max()).getCollection();
  
  tmpImPred.clear();

  // les predecesseurs immediats sont les maximaux de l'ideal obtenu
  // il suffit de former un SetOfElements
  for (it = tmpMax.begin() ; it != tmpMax.end() ; it++)
  {
    saveIdeal = tmpIdeal;
    tmpElement.clear();
    num = it -> getNumber();
    tmpElement.setNumber(num);
    tmpSetOfInt = saveIdeal.getJnumbers();
    tmpSetOfInt.erase(num);
    tmpElement.setItemSet(tmpSetOfInt);
    tmpImPred.add(tmpElement);
  }

  // on retourne l'ensemble de predecesseurs immediats
  return (tmpImPred);
}


// ==============================================================

void Order::affiche()
{
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
    // pour un ordre on affiche
    // l'ensemble J
    cout << endl;
    cout << "Ensemble J : " << endl;
    J.affiche();
    cout << endl;
   
    map<int, SetOfElements>::iterator itMap;
    set<Element>::iterator itSet;
    set<Element> tmpSet;
    
    // l'ensemble des ImSucc
    cout << endl;
    cout << "Ensemble des ImSucc : " << endl;
    for(itMap = imSucc.begin() ; itMap != imSucc.end() ; itMap++)
    {
        cout << "[" << itMap -> first << "] = ";
        tmpSet = (itMap -> second).getCollection();
        for (itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++)
        {
    cout << "\t";
    //cout << itSet -> getNumber() << "   ";
    itSet -> affiche();
  }
  cout << endl;
    }

    // l'ensemble des ImPred
    cout << endl;
    cout << "Ensemble des ImPred : " << endl;
    for(itMap = imPred.begin() ; itMap != imPred.end() ; itMap++)
    {
        cout << "[" << itMap -> first << "] = ";
        tmpSet = (itMap -> second).getCollection();
        for (itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++)
        {
    cout << "\t";
    //cout << itSet -> getNumber() << "   ";
    itSet -> affiche();
  }
  cout << endl;
    }
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
}

// ==============================================================

void Order::genGraph(string filename) {
  Table tbl;
  tbl.setName(getTable());
	tbl.rewind();
  
  FILE *fp = fopen(filename.c_str(),"wb");
  fprintf(fp,"graph G {\nrankdir=BT;\nnode [color=cyan, style=filled];\nnodesep=0.80;\n");

  for(map<int, SetOfElements>::iterator itMap = imSucc.begin() ; itMap != imSucc.end() ; itMap++) {
    
    fprintf(fp,"\"%s\" -- {",tbl.getNameOfSetOfInt(getJ().getSetByNumber(itMap->first)).c_str());
    set<Element> tmpSet = (itMap -> second).getCollection();
    for (set<Element>::iterator itSet = tmpSet.begin() ; itSet != tmpSet.end() ; itSet++) {
      fprintf(fp,"\"%s\"; ",tbl.getNameOfSetOfInt(itSet->getItemSet()).c_str());
    }
    fprintf(fp,"}\n");
  }

  fprintf(fp,"}");
  fclose(fp);
}
