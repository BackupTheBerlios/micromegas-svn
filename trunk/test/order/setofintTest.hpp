// itemsetTest.h
#ifndef SETOFINTTEST_H
#define SETOFINTTEST_H


#include <cppunit/extensions/HelperMacros.h>


class SetOfIntTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(SetOfIntTest);
  CPPUNIT_TEST(testInter);
  CPPUNIT_TEST(testMinus);
  CPPUNIT_TEST(testInclude);
  CPPUNIT_TEST(testUnion);
  CPPUNIT_TEST(testDif);
  CPPUNIT_TEST_SUITE_END();

private:
  SetOfInt* fixture1;
  SetOfInt* fixture2;

public:
  virtual void setUp();
  virtual void tearDown();
  void testInter();
  void testMinus();
  void testInclude();
  void testUnion();
  void testDif();
};

#endif
