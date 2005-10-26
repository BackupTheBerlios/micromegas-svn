// tableTest.cpp

#include "../../src/order/table.hpp"
#include "tableTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(TableTest);

//==========================================================

void TableTest::setUp()
{
  fixture1=new Table();
  fixture2=new Table();
  fixture3=new Table();
}

//==========================================================

void TableTest::tearDown()
{
  delete fixture1;
  delete fixture2;
  delete fixture3;
}

//==========================================================

void TableTest::charger(string &filename)
{
  string nom=filename;
  
  fixture1->clear();
  fixture1->setName(nom);
  fixture1->rewind();
  
  tuples1.resize(fixture1->getNbTuples());
  
  for(int i=0;i<fixture1->getNbTuples();++i)
  {
    tuples1[i]=fixture1->readTuple();
  }
    
}

//==========================================================

void TableTest::charger2(string &filename)
{
  string nom=filename;
  
  fixture2->clear();
  fixture2->setName(nom);
  fixture2->rewind();
  
  tuples2.resize(fixture2->getNbTuples());
  
  for(int i=0;i<fixture2->getNbTuples();++i)
  {
    tuples2[i]=fixture2->readTuple();
  }
    
}


//==========================================================

void TableTest::charger3(string &filename)
{
  string nom=filename;
  
  fixture3->clear();
  fixture3->setName(nom);
  fixture3->rewind();
  
  tuples3.resize(fixture3->getNbTuples());
  
  for(int i=0;i<fixture3->getNbTuples();++i)
  {
    tuples3[i]=fixture3->readTuple();
  }
    
}


//==========================================================

void TableTest::sauver(string &filename)
{
  fixture1->setName(filename);
  
  fixture1->writeHeader();
  
  for(int i=0;i<fixture1->getNbTuples();++i)
  {
    fixture1->writeTuple(tuples1[i]);
  }
  
  fixture1->writeEnd();
  
}

//==========================================================

void TableTest::testCharger()
{
  string nom="tableTest.xml";
  charger(nom);
  
  string tmp="tableTest";
  int nbtu=6;
  int nbit=5;
  
  map<string,int> map_tmp;
  
  vector<string> items;
  items.resize(nbit);
  
  items[0]="Whisky";
  items[1]="Cacahuetes";
  items[2]="Coca";
  items[3]="Lessive";
  items[4]="Assouplissant";

  for(int i=0;i<nbit;++i)
  {
    map_tmp[items[i]]=i;
  }
   
  fixture2->setName(tmp);
  fixture2->setNbTuples(nbtu);
  fixture2->setNbItems(nbit);
  fixture2->setMapping(map_tmp);
  
  tuples2.resize(nbtu);
  
  tuples2[0].insert(0);
  tuples2[0].insert(1);
  tuples2[0].insert(2);
  
  tuples2[1].insert(0);
  tuples2[1].insert(1);
  
  tuples2[2].insert(0);
  
  tuples2[3].insert(1);
  tuples2[3].insert(4);
  tuples2[3].insert(3);
  
  tuples2[4].insert(3);
  tuples2[4].insert(4);
  
  tuples2[5].insert(0);
  tuples2[5].insert(4);
  
  
  CPPUNIT_ASSERT(fixture1->getName()==fixture2->getName());
  CPPUNIT_ASSERT(fixture1->getNbTuples()==fixture2->getNbTuples());
  CPPUNIT_ASSERT(fixture1->getNbItems()==fixture2->getNbItems());
  CPPUNIT_ASSERT(fixture1->getMapping()==fixture2->getMapping());
  CPPUNIT_ASSERT(tuples1==tuples2);
  
}

//==========================================================

void TableTest::testSauver()
{
  string originale="tableTest.xml";
  charger(originale);

  string nom1="tableTestSauv1.xml";
  string nom2="tableTestSauv2.xml";
  sauver(nom1);
  sauver(nom2);
  

  charger3(nom1);
  charger2(nom2);
  
  
  CPPUNIT_ASSERT(fixture3->getNbTuples()==fixture2->getNbTuples());
  CPPUNIT_ASSERT(fixture3->getNbItems()==fixture2->getNbItems());
  CPPUNIT_ASSERT(fixture3->getMapping()==fixture2->getMapping());
  CPPUNIT_ASSERT(tuples3==tuples2);
  
}


//==========================================================

void TableTest::testCircu()
{
  string originale="wine_wineTable.table.xml";
  charger(originale);

  string nom1="tableTestSauv_wine1.xml";
  string nom2="tableTestSauv_wine2.xml";
  sauver(nom1);
  sauver(nom2);
  

  charger3(nom1);
  charger2(nom2);
  
  
  CPPUNIT_ASSERT(fixture3->getNbTuples()==fixture2->getNbTuples());
  CPPUNIT_ASSERT(fixture3->getNbItems()==fixture2->getNbItems());
  CPPUNIT_ASSERT(fixture3->getMapping()==fixture2->getMapping());
  CPPUNIT_ASSERT(tuples3==tuples2);
  
}


//==========================================================

void TableTest::testCircu2()
{
  string originale="mushrooms_mushroomsTable.table.xml";
  charger(originale);

  string nom1="tableTestSauv_mush1.xml";
  string nom2="tableTestSauv_mush2.xml";
  sauver(nom1);
  sauver(nom2);
  

  charger3(nom1);
  charger2(nom2);
  
  
  CPPUNIT_ASSERT(fixture3->getNbTuples()==fixture2->getNbTuples());
  CPPUNIT_ASSERT(fixture3->getNbItems()==fixture2->getNbItems());
  CPPUNIT_ASSERT(fixture3->getMapping()==fixture2->getMapping());
  CPPUNIT_ASSERT(tuples3==tuples2);
  
}


//==========================================================

/*Permet de convertir une map<char*,int> en map<string,int> afin de pouvoir
comparer deux maps.
En effet, si la cle est un char*, les cles sont rangees par ordre des valeurs
de pointeurs, et non pas par ordre alphabetique
De plus, deux map ayant une cle en char* peuvent etre detectee differentes,
alors qu'elle sont egales, simplement parce que la comparaison est faite sur
l'adresse de la cle, et on pas sur la cle elle meme*/

map<string,int> TableTest::convertir(map<char*,int> tmp)
{
  map<string,int> ret;
  
  map<char*,int>::iterator it;
  
  for(it=tmp.begin();it!=tmp.end();++it)
  {
    string convert=it->first;
    ret[convert]=it->second;
  }
  
  return ret;
}

//==========================================================
