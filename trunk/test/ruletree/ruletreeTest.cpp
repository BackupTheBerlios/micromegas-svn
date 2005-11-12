// ruletreeTest.cpp

#include "../../src/ruletree/ruletree.hpp"
#include "ruletreeTest.hpp"


//==========================================================

CPPUNIT_TEST_SUITE_REGISTRATION(RuleTreeTest);

//==========================================================

void RuleTreeTest::setUp()
{
  fixture1=new RuleTree();
  fixture2=new RuleTree();
}

//==========================================================

void RuleTreeTest::tearDown()
{
  delete fixture1;
  delete fixture2;
}

//==========================================================

void RuleTreeTest::testloadsave()
{
  fixture1->setName("demo.arbo.xml");
  fixture1->load();
  fixture1->save("demo.arbo.xml_2");
  fixture2->setName("demo.arbo.xml_2");
  fixture2->load();
  fixture2->save("demo.arbo.xml_2");
}

