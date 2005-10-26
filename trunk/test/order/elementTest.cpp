// elementTest.cpp

#include "../../src/order/element.hpp"
#include "elementTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(ElementTest);

//==========================================================

void ElementTest::setUp()
{
  fixture1=new Element();
  fixture2=new Element();
}

//==========================================================

void ElementTest::tearDown()
{
  delete fixture1;
  delete fixture2;
}

//==========================================================

void ElementTest::testaffectation()
{
  for(int i=0; i<100; ++i)
  {
    fixture1->setNumber(i);
    *fixture2=*fixture1;
    CPPUNIT_ASSERT(*fixture1==*fixture2);
    CPPUNIT_ASSERT(*fixture2==*fixture1);
  }
}

//==========================================================

void ElementTest::test_dif_et_egal()
{
  for(int j=0; j<100; ++j)
  {
    for(int i=1; i<100; ++i)
    {
      fixture2->setNumber(i);
      if(i==j)
      {
        fixture1->setNumber(j-1);
      }
      else
      {
        fixture1->setNumber(j);
      }
      CPPUNIT_ASSERT(!(*fixture2==*fixture1));
      CPPUNIT_ASSERT(*fixture2!=*fixture1);
    }
  }
}

//==========================================================

void ElementTest::testinferieur()
{
  fixture1->setNumber(1);
    
  for(int i=2; i<1000; ++i)
  {
    fixture2->setNumber(i);
    CPPUNIT_ASSERT(!(*fixture2<*fixture1));
    CPPUNIT_ASSERT(*fixture1<*fixture2);
  }
  
  for(int i=2; i<999; ++i)
  {
    fixture1->setNumber(i);
    CPPUNIT_ASSERT(!(*fixture2<*fixture1));
    CPPUNIT_ASSERT(*fixture1<*fixture2);
  }
  
}

//==========================================================
