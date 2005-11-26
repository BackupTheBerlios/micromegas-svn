// orderTest.cpp

#include "../../src/order/order.hpp"
#include "orderTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(OrderTest);

//==========================================================

void OrderTest::setUp()
{
  fixture1=new Order();
  fixture2=new Order();
  
}

//==========================================================

void OrderTest::tearDown()
{
  delete fixture1;
  delete fixture2;
}

//==========================================================

void OrderTest::testPred()
{
  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  
  fixture1->load();
  //fixture1->affiche();
  
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(2);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(1);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImPred(tmpElem));
  
  /******/
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  tmpSOE.add(tmpElem);
   
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImPred(tmpElem));
  
  /******/
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(1);
  
  tmpSOE.add(tmpElem);
   
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(6);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(7);
  
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImPred(tmpElem));
  
  /*****/
  
  tmpSOE.clear();
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImPred(tmpElem));
  
}

//==========================================================

void OrderTest::testSucc()
{
  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();  
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
  
  
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(1);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(6);
  
  tmpSOE.add(tmpElem);
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImSucc(tmpElem));
  
  /******/
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(7);
  
  tmpSOE.add(tmpElem);
   
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImSucc(tmpElem));
  
  /******/
  
  tmpSOE.clear();
  
  /*--*/
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(7);
  
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->getImSucc(tmpElem));
  
  
}

//==========================================================

void OrderTest::testMin()
{
  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();  

  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
    
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(2);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE.add(tmpElem);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->min());

}
  
  
//==========================================================
  
void OrderTest::testMax()
{

  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();  

  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
    
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(7);
  
  tmpSOE.add(tmpElem);
  
  CPPUNIT_ASSERT(tmpSOE==fixture1->max());
  
}

//==========================================================
  
void OrderTest::testIdeal()
{

  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
  SetOfElements tmpSOEparam;
  
  tmpSOE.clear();
  tmpSOEparam.clear();
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(2);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(1);
  
  tmpSOEparam.add(tmpElem);
  tmpSOE.add(tmpElem);
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(6);
  
  tmpSOEparam.add(tmpElem);
  tmpSOE.add(tmpElem);
  
  CPPUNIT_ASSERT(tmpSOE==(fixture1->getIdeal(tmpSOEparam)).getJ());
  
  
  tmpSOE.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  tmpSOE.add(tmpElem);
  
  CPPUNIT_ASSERT(tmpSOE==(fixture1->getIdeal(tmpSOE)).getJ());
  
}

//==========================================================
  
void OrderTest::testFilter()
{

  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
  SetOfElements tmpSOEparam;
  
  tmpSOE.clear();  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(2);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  tmpSOE.add(tmpElem);
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  CPPUNIT_ASSERT(tmpSOE==(fixture1->removeFilter(tmpElem)).getJ());
  
  
  
  tmpSOE.clear();  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(1);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(2);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(3);
  
  tmpSOE.add(tmpElem);

  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(6);
  
  tmpSOE.add(tmpElem);  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE.add(tmpElem);

  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
    
  CPPUNIT_ASSERT(tmpSOE==(fixture1->removeFilter(tmpElem)).getJ());
  
}

//==========================================================
  
void OrderTest::testImSuccIdeal()
{

  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE;
  
  tmpSOE.clear();
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  tmpSOE.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE.add(tmpElem);
    
  Order tmpOrder;
  tmpOrder.clear();
  tmpOrder.setJ( (fixture1->getJ()).SoE_minus((fixture1->getIdeal(tmpSOE)).getJ() ) );
  
  cout<<"TEST"<<endl;
  fixture1->imSuccIdeal(tmpSOE).affiche();
  //fixture1->getIdeal(tmpSOE).affiche();
  //cout<<"Sans le min"<<endl;
  //tmpOrder.affiche();
  cout<<"Avec le min"<<endl;
  (tmpOrder.min()).affiche();
  cout<<endl<<endl;
  
  //Le test echoue, mais les numéros des élements sont correctes.
  // Les numéro d'item de ces élements ne concordent effectivement
  // pas. Ceci est du à l'algorithme utilisé pour ImSuccIdeal,
  // mais le résultat obtenu est bien celui escompté avec un tel
  // algorithme. Est-ce le bon ?
  CPPUNIT_ASSERT((fixture1->imSuccIdeal(tmpSOE))==tmpOrder.min());
  
}

//==========================================================
  
void OrderTest::testImPredIdeal()
{
  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE1;
  SetOfElements tmpSOE2;

  tmpSOE1.clear();
  tmpSOE1.setName(nom);
  tmpSOE1.setTable(nom2);
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(2);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(7);
  
  tmpSOE1.add(tmpElem);

  tmpSOE2.clear();
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  tmpSOE2.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE2.add(tmpElem);
  
  cout<<"TEST"<<endl;
  tmpSOE2 = fixture1->imPredIdeal(tmpSOE2);
  tmpSOE2.setName(nom);
  tmpSOE2.setTable(nom2);
  tmpSOE2.affiche();
  cout<<"resultat"<<endl;
  tmpSOE1.affiche();
  cout<<endl<<endl;
  
  CPPUNIT_ASSERT(tmpSOE1==fixture1->imPredIdeal(tmpSOE2));
}

void OrderTest::testImPredIdeal2()
{
  string nom="collecOrderTest2.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest2.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  SetOfInt tmpItem;
  Element tmpElem;
  SetOfElements tmpSOE1;
  SetOfElements tmpSOE2;

  tmpSOE1.clear();

  tmpSOE2.clear();
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(0);
  tmpItem.insert(1);
  tmpItem.insert(3);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(5);
  
  tmpSOE2.add(tmpElem);
  
  
  tmpItem.clear();
  tmpElem.clear();
  
  tmpItem.insert(1);
  tmpItem.insert(2);
  
  tmpElem.setItemSet(tmpItem);
  tmpElem.setNumber(4);
  
  tmpSOE2.add(tmpElem);
  
  CPPUNIT_ASSERT(tmpSOE1==fixture1->imPredIdeal(tmpSOE2));
  
}

//==========================================================
  
void OrderTest::testLoadSave()
{
  string nom="collecOrderTest.xml";
  fixture1->setName((char*)nom.c_str());
  
  string nom2="tableOrderTest.xml";
  fixture1->setTable((char*)nom2.c_str());
  
  
  fixture1->load();
  
  string nom3="collecOrderTest1.xml";
  fixture1->setName((char*)nom3.c_str());
  
  fixture1->save();
  
  fixture2->setName((char*)nom3.c_str());
  fixture2->load();
  
    CPPUNIT_ASSERT(fixture1->getJ()==fixture2->getJ());

}







