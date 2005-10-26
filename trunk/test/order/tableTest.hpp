// tableTest.h
#ifndef TABLETEST_H
#define TABLETEST_H


#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include "../../src/order/setofint.hpp"

class TableTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(TableTest);
  CPPUNIT_TEST(testCharger);
  CPPUNIT_TEST(testSauver);
  CPPUNIT_TEST(testCircu);
  //CPPUNIT_TEST(testCircu2);
  CPPUNIT_TEST_SUITE_END();


private:
  Table* fixture1;  
  Table* fixture2;
  Table* fixture3;
  vector<SetOfInt> tuples1;
  vector<SetOfInt> tuples2;
  vector<SetOfInt> tuples3;
  
public:
  virtual void setUp();
  virtual void tearDown();
  map<string,int> convertir(map<char*,int> tmp);
  void charger(string &filename);
  void charger2(string &filename);
  void charger3(string &filename);
  void sauver(string &filename);
  void testCharger();
  void testSauver();
  void testCircu();
  void testCircu2();

};


#endif
