// orderTest.h
#ifndef ORDERTEST_H
#define ORDERTEST_H


#include <cppunit/extensions/HelperMacros.h>


class OrderTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(OrderTest);
  CPPUNIT_TEST(testPred);
  CPPUNIT_TEST(testSucc);
  CPPUNIT_TEST(testMin);
  CPPUNIT_TEST(testMax);
  CPPUNIT_TEST(testIdeal);
  CPPUNIT_TEST(testFilter);
  CPPUNIT_TEST(testLoadSave);
  //CPPUNIT_TEST(testImSuccIdeal);
  //CPPUNIT_TEST(testImPredIdeal);
  //CPPUNIT_TEST(testImPredIdeal2);
  CPPUNIT_TEST_SUITE_END();

private:
  Order* fixture1;
  Order* fixture2;
  
  
public:
  virtual void setUp();
  virtual void tearDown();
  void testPred();
  void testSucc();
  void testMin();
  void testMax();
  void testIdeal();
  void testFilter();
  void testImSuccIdeal();
  void testImPredIdeal();
  void testImPredIdeal2();
  void testLoadSave();
};


#endif
