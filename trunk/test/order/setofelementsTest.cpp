// setofelementstest.cpp

#include "../../src/order/setofelements.hpp"
#include "setofelementsTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(SetOfElementstest);

//==========================================================

void SetOfElementstest::setUp()
{
  fixture1=new SetOfElements();
  fixture2=new SetOfElements();
  fixture3=new SetOfElements();
  fix_table=new Table();
  fix_table2=new Table();
}

//==========================================================

void SetOfElementstest::tearDown()
{
  delete fixture1;
  delete fixture2;
  delete fixture3;
  delete fix_table;
  delete fix_table2;
}

//==========================================================

void SetOfElementstest::test_load_save()
{
  
  string tmp_nom="tableTest.xml";
  
  generator_collec(tmp_nom);
  
  fixture1->setName("collecTest.xml");
  fixture1->save();
  
  fixture2->setName("collecTest.xml");
  fixture2->load();
  
  //fixture1->affiche();
  //fixture2->affiche();
  CPPUNIT_ASSERT((*fixture1)==(*fixture2));
}

//==========================================================

void SetOfElementstest::test_closureAll()
{
  string tmp_nom="tableTest.xml";
  
  generator_closure(tmp_nom);
  
  
  fixture1->closureAll((char*)tmp_nom.c_str());
  
  
  Element tmp_elem;
  SetOfInt tmp_item;
  
  tmp_elem.setNumber(0);
  tmp_item.insert(0);
  tmp_elem.setItemSet(tmp_item);
  fixture2->add(tmp_elem);
  
  tmp_elem.clear();
  tmp_item.clear();
  
  
  
  tmp_elem.setNumber(1);
  tmp_item.insert(1);
  tmp_elem.setItemSet(tmp_item);
  fixture2->add(tmp_elem);
  
  tmp_elem.clear();
  tmp_item.clear();
  
  
  
  tmp_elem.setNumber(2);
  tmp_item.insert(0);
  tmp_item.insert(1);
  tmp_item.insert(2);
  tmp_elem.setItemSet(tmp_item);
  fixture2->add(tmp_elem);
  
  tmp_elem.clear();
  tmp_item.clear();
  
  
  
  tmp_elem.setNumber(3);
  tmp_item.insert(3);
  tmp_item.insert(4);
  tmp_elem.setItemSet(tmp_item);
  fixture2->add(tmp_elem);
  
  tmp_elem.clear();
  tmp_item.clear();
  
  
  
  tmp_elem.setNumber(4);
  tmp_item.insert(4);
  tmp_elem.setItemSet(tmp_item);
  fixture2->add(tmp_elem);
  
  tmp_elem.clear();
  tmp_item.clear();
  
  CPPUNIT_ASSERT((*fixture1)==(*fixture2));
  
}

//==========================================================

void SetOfElementstest::test_getNumbers()
{
  string tmp_nom="wine_wineTable.table.xml";
  int nb_tuples;
  
  nb_tuples=generator_collec(tmp_nom);
  
  SetOfInt tmp_item;
  
  for(int i=1;i<=nb_tuples;++i)
  {
    tmp_item.insert(i);
  }
  
  CPPUNIT_ASSERT(fixture1->getNumbers()==tmp_item);
  
}

//==========================================================

void SetOfElementstest::test_getNumbers2()
{
  
  string tmp_nom="mushrooms_mushroomsTable.table.xml";
  int nb_tuples;
  
  nb_tuples=generator_collec(tmp_nom);
  
  SetOfInt tmp_item;
  
  for(int i=1;i<=nb_tuples;++i)
  {
    tmp_item.insert(i);
  }
  
  CPPUNIT_ASSERT(fixture1->getNumbers()==tmp_item);
  
}

//==========================================================

void SetOfElementstest::test_unionSets()
{
  string tmp_nom="tableTest.xml";
      
  //On génère avec deux fois la même table
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom);
  
  (*fixture3)=fixture1->unionSets((*fixture2));
  
  CPPUNIT_ASSERT((*fixture1)==(*fixture3));
  CPPUNIT_ASSERT((*fixture2)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_unionSets2()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest2.xml";
      
  //La table 2 contient plus de tuples que la 1
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->unionSets((*fixture2));
  
  CPPUNIT_ASSERT((*fixture1)!=(*fixture3));
  CPPUNIT_ASSERT((*fixture2)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_unionSets3()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest3.xml";
      
  //La table 3 contient les tulples de la 1 plus des doublons
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->unionSets((*fixture2));
  CPPUNIT_ASSERT((*fixture1)==(*fixture3));
  CPPUNIT_ASSERT((*fixture2)!=(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_unionSets4()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest4.xml";    
  
  //La table 4 contient les tuples de la 1 dans un autre ordre
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->unionSets((*fixture2));
  CPPUNIT_ASSERT((*fixture1)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_union()
{
  string tmp_nom="tableTest.xml";
      
  //On génère avec deux fois la même table
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom);
  
  (*fixture3)=fixture1->SoE_union((*fixture2));
  
  CPPUNIT_ASSERT((*fixture1)==(*fixture3));
  CPPUNIT_ASSERT((*fixture2)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_union2()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest2.xml";
      
  //La table 2 contient plus de tuples que la 1
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->SoE_union((*fixture2));
  
  CPPUNIT_ASSERT((*fixture1)!=(*fixture3));
  CPPUNIT_ASSERT((*fixture2)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_union3()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest3.xml";
      
  //La table 3 contient les tulples de la 1 plus des doublons
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->SoE_union((*fixture2));
  
  CPPUNIT_ASSERT((*fixture1)!=(*fixture3));
  CPPUNIT_ASSERT((*fixture2)==(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_union4()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest4.xml";    
  
  //La table 4 contient les tuples de la 1 dans un autre ordre
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->SoE_union((*fixture2));

  CPPUNIT_ASSERT((*fixture1)!=(*fixture2));
  CPPUNIT_ASSERT((*fixture2)!=(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_minus()
{
  string tmp_nom="tableTest.xml";
  
  SetOfElements tmp_SOE;
  tmp_SOE.clear();    
  //On génère avec deux fois la même table
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom);
  
  (*fixture3)=fixture1->SoE_minus((*fixture2));
  
  CPPUNIT_ASSERT((*fixture3)==tmp_SOE);
  
}

//==========================================================

void SetOfElementstest::test_SoE_minus2()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest2.xml";
      
  //La table 2 contient plus de tuples que la 1
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture2->SoE_minus((*fixture1));
  
  CPPUNIT_ASSERT((*fixture1)!=(*fixture3));
  CPPUNIT_ASSERT((*fixture2)!=(*fixture3));
  
}

//==========================================================

void SetOfElementstest::test_SoE_minus3()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest3.xml";
  
  SetOfElements tmp_SOE;
  tmp_SOE.clear(); 
      
  //La table 3 contient les tulples de la 1 plus des doublons
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture1->SoE_minus((*fixture2));
  
  CPPUNIT_ASSERT((*fixture3)==tmp_SOE);
  
}

//==========================================================

void SetOfElementstest::test_SoE_minus4()
{
  string tmp_nom="tableTest.xml";
  string tmp_nom2="tableTest4.xml";    
  
  SetOfElements tmp_SOE;
  tmp_SOE.clear();
  
  //La table 4 contient les tuples de la 1 dans un autre ordre
  generator_collec(tmp_nom);
  generator_collec2(tmp_nom2);
  
  (*fixture3)=fixture2->SoE_minus((*fixture1));
  
  CPPUNIT_ASSERT((*fixture3)==tmp_SOE);
  
}

//==========================================================

int SetOfElementstest::generator_collec(string nom_table)
{
  Element tmp_elem;
  SetOfInt tmp_item;
  
  fixture1->setTable((char*)nom_table.c_str());
  
    
  fix_table->clear();
  fix_table->setName(nom_table);
  fix_table->rewind();
  
  for(int i=0;i<fix_table->getNbTuples();++i)
  {
    tmp_elem.clear();
    tmp_item=fix_table->readTuple();
    tmp_elem.setItemSet(tmp_item);
    tmp_elem.setNumber(i+1);
    
    fixture1->add(tmp_elem);
  }
  
  int ret=fix_table->getNbTuples();
  
  //fix_table->close();
  
  return ret;
  
}

//==========================================================

int SetOfElementstest::generator_collec2(string nom_table)
{
  Element tmp_elem;
  SetOfInt tmp_item;
  
  fixture2->setTable((char*)nom_table.c_str());
  
    
  fix_table2->clear();
  fix_table2->setName(nom_table);
  fix_table2->rewind();
  
  for(int i=0;i<fix_table2->getNbTuples();++i)
  {
    tmp_elem.clear();
    tmp_item=fix_table2->readTuple();
    tmp_elem.setItemSet(tmp_item);
    tmp_elem.setNumber(i+1);
    
    fixture2->add(tmp_elem);
  }
  
  int ret=fix_table2->getNbTuples();
  
  //fix_table2->close();
  
  return ret;
  
}

//==========================================================

void SetOfElementstest::generator_closure(string nom_table)
{
  fixture1->setTable((char*)nom_table.c_str());
  
  fix_table->clear();
  fix_table->setName(nom_table);
  fix_table->rewind();
  
  map<string,int> tmp_map;
  Element tmp_elem;
  map<string,int>::iterator it;
  
  tmp_map=fix_table->getMapping();
  
  for(it=tmp_map.begin();it!=tmp_map.end();++it)
  {
    tmp_elem.clear();
    tmp_elem.setNumber(it->second);
    
    fixture1->add(tmp_elem); 
  }
  
  //fix_table->close();
}

//==========================================================

void SetOfElementstest::test_setSup() {
  fixture1->setSup("demo.table.xml");
  //printf("\n\n\n");
  //fixture1->affiche();
  //printf("\n\n\n");
  fflush(NULL);
}

void SetOfElementstest::test_setInf() {
  fixture1->setInf("demo.table.xml");
  //printf("\n\n\n");
  //fixture1->affiche();
  //printf("\n\n\n");
  fflush(NULL);
}


