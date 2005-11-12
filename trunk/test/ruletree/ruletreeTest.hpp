// ruletreeTest.h
#ifndef RULETREETEST_H
#define RULETREETEST_H


#include <cppunit/extensions/HelperMacros.h>


class RuleTreeTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(RuleTreeTest);
  CPPUNIT_TEST(testloadsave);
  CPPUNIT_TEST_SUITE_END();

private:
  RuleTree* fixture1;
  RuleTree* fixture2;

public:
  virtual void setUp();
  virtual void tearDown();
  void testloadsave();
};

#endif
