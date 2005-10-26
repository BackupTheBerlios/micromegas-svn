// elementTest.h
#ifndef ELEMENTTEST_H
#define ELEMENTTEST_H


#include <cppunit/extensions/HelperMacros.h>


class ElementTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(ElementTest);
  CPPUNIT_TEST(test_dif_et_egal);
  CPPUNIT_TEST(testaffectation);
  CPPUNIT_TEST(testinferieur);
  
  CPPUNIT_TEST_SUITE_END();


private:
  Element* fixture1;
  Element* fixture2;

public:
  virtual void setUp();
  virtual void tearDown();
  void testaffectation();
  void test_dif_et_egal();
  void testinferieur();

};


#endif
