// setofintTest.cpp

#include "../../src/order/setofint.hpp"
#include "setofintTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(SetOfIntTest);

//==========================================================

void SetOfIntTest::setUp()
{
  fixture1=new SetOfInt();
  fixture2=new SetOfInt();

  fixture1->insert(1);
  fixture1->insert(2);
  fixture1->insert(3);

  fixture2->insert(2);
  fixture2->insert(3);
}

//==========================================================

void SetOfIntTest::tearDown()
{
  delete fixture1;
  delete fixture2;
}

//==========================================================

void SetOfIntTest::testInter()
{
  SetOfInt* fixture3=new SetOfInt();
  fixture3->insert(2);
  fixture3->insert(3);
  
  for(int i=4; i<1000; ++i)
  {
    CPPUNIT_ASSERT(fixture1->I_intersection(*fixture2)==*fixture3);
    fixture2->insert(i);
  }
  
  for(int i=4; i<1000; ++i)
  {
    fixture1->insert(i);
    fixture3->insert(i);
    CPPUNIT_ASSERT(fixture1->I_intersection(*fixture2)==*fixture3);
  }

  for(int i=4; i<1000; ++i)
  {
    fixture1->insert(i);
    fixture2->erase(i);
  }
  
  delete fixture3;
}


//==========================================================

void SetOfIntTest::testMinus()
{
  SetOfInt* fixture3=new SetOfInt();
  fixture3->insert(1);
  
  for(int i=4; i<1000; ++i)
  {
    fixture1->insert(i);
    fixture2->insert(i);
    CPPUNIT_ASSERT(fixture1->I_minus(*fixture2)==*fixture3);
  }
  
  for(int i=999; i>3; --i)
  {
    fixture1->erase(i);
    CPPUNIT_ASSERT(fixture1->I_minus(*fixture2)==*fixture3);
  }
  
  for(int i=999; i>3; --i)
  {
    fixture2->erase(i);
    CPPUNIT_ASSERT(fixture1->I_minus(*fixture2)==*fixture3);
  }
    
  delete fixture3;
}

//==========================================================

void SetOfIntTest::testInclude()
{

  CPPUNIT_ASSERT(fixture1->I_includes(*fixture2));
  
  SetOfInt* fixture3=new SetOfInt();

  fixture3->insert(1);
  fixture3->insert(2);
  fixture3->insert(3);
  
  CPPUNIT_ASSERT(fixture1->I_includes(*fixture3));
  CPPUNIT_ASSERT(fixture3->I_includes(*fixture1));
  CPPUNIT_ASSERT(fixture3->I_includes(*fixture2));
  CPPUNIT_ASSERT(fixture1->I_includes(*fixture2));
  CPPUNIT_ASSERT(fixture2->I_includes(*fixture2));
  CPPUNIT_ASSERT(fixture1->I_includes(*fixture1));
  CPPUNIT_ASSERT(!(fixture2->I_includes(*fixture1)));
  
  for(int i=0; i<1000; ++i)
  {
    fixture1->insert(i);
    CPPUNIT_ASSERT(fixture1->I_includes(*fixture3));
    CPPUNIT_ASSERT(!(fixture3->I_includes(*fixture1)));
  }
  
  fixture3->erase(1);
  fixture3->erase(2);
  fixture3->erase(3);

  for(int i=999; i>3; --i)
  {
    CPPUNIT_ASSERT(fixture1->I_includes(*fixture3));
    CPPUNIT_ASSERT(!(fixture3->I_includes(*fixture1)));
  }
  
  CPPUNIT_ASSERT(fixture2->I_includes(*fixture3));
    
  delete fixture3;
  
}

//==========================================================

void SetOfIntTest::testUnion()
{
  SetOfInt* fixture3=new SetOfInt();
  fixture3->insert(3);
  fixture3->insert(4);
  fixture3->insert(5);
  
  SetOfInt* fixture4=new SetOfInt();
  fixture4->insert(1);
  fixture4->insert(2);
  fixture4->insert(3);
  fixture4->insert(4);
  fixture4->insert(5);

  CPPUNIT_ASSERT(!(fixture1->I_union(*fixture3)==*fixture3));
  
  for(int i=6; i<1000; ++i)
  {
    fixture3->insert(i);
    fixture4->insert(i);  
    CPPUNIT_ASSERT(fixture3->I_union(*fixture1)==*fixture4);    
    CPPUNIT_ASSERT(fixture1->I_union(*fixture3)==*fixture4);
  }
  
  fixture3->clear();
  CPPUNIT_ASSERT(fixture1->I_union(*fixture3)==*fixture1);
  CPPUNIT_ASSERT(fixture3->I_union(*fixture1)==*fixture1);
  
  fixture4->clear();
  CPPUNIT_ASSERT(fixture4->I_union(*fixture4)==*fixture4);
  CPPUNIT_ASSERT(fixture4->I_union(*fixture4)==*fixture3);
  CPPUNIT_ASSERT(fixture4->I_union(*fixture3)==*fixture4);
  CPPUNIT_ASSERT(fixture3->I_union(*fixture4)==*fixture3);
  
  delete fixture3;
  delete fixture4;
}

//==========================================================

void SetOfIntTest::testDif()
{
  SetOfInt* fixture3=new SetOfInt();
  fixture3->insert(4);
  fixture3->insert(5);
  fixture3->insert(6);
  
  SetOfInt* fixture4=new SetOfInt();

  fixture4->insert(1);
  fixture4->insert(2);
  fixture4->insert(3);
  
  
  CPPUNIT_ASSERT((*fixture1)!=(*fixture3));
  CPPUNIT_ASSERT((*fixture1)!=(*fixture2));
  
  CPPUNIT_ASSERT(*fixture1==*fixture4);
  CPPUNIT_ASSERT(!(*fixture1!=*fixture4));
  
  for(int i=4; i<100;++i)
  {
    fixture4->insert(i);
    CPPUNIT_ASSERT(*fixture3!=*fixture4);
  }
  
  for(int i=4; i<100;++i)
  {
    fixture3->insert(i+3);
    CPPUNIT_ASSERT(*fixture3!=*fixture4);
  }
  
  fixture3->clear();
  CPPUNIT_ASSERT(*fixture3!=*fixture4);
  CPPUNIT_ASSERT(!(*fixture3==*fixture4));
  
  fixture4->clear();
  CPPUNIT_ASSERT(!(*fixture3!=*fixture4));
  CPPUNIT_ASSERT(*fixture3==*fixture4);
  
  delete fixture3;
  delete fixture4;
}

