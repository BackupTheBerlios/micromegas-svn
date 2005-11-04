// setofelementstest.h
#ifndef SETOFELEMENTSTEST_H
#define SETOFELEMENTSTEST_H


#include <cppunit/extensions/HelperMacros.h>


class SetOfElementstest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE(SetOfElementstest);
  CPPUNIT_TEST(test_load_save);
  CPPUNIT_TEST(test_closureAll);
  CPPUNIT_TEST(test_getNumbers);
  //CPPUNIT_TEST(test_getNumbers2);
  CPPUNIT_TEST(test_unionSets);
  CPPUNIT_TEST(test_unionSets2);
  CPPUNIT_TEST(test_unionSets3);
  CPPUNIT_TEST(test_unionSets4);
  CPPUNIT_TEST(test_SoE_union);
  CPPUNIT_TEST(test_SoE_union2);
  CPPUNIT_TEST(test_SoE_union3);
  CPPUNIT_TEST(test_SoE_union4);
  CPPUNIT_TEST(test_SoE_minus);
  CPPUNIT_TEST(test_SoE_minus2);
  CPPUNIT_TEST(test_SoE_minus3);
  CPPUNIT_TEST(test_SoE_minus4);
  CPPUNIT_TEST(test_setSup);
  CPPUNIT_TEST(test_setInf);
  CPPUNIT_TEST_SUITE_END();


private:
  SetOfElements* fixture1;
  SetOfElements* fixture2;
  SetOfElements* fixture3;
  Table* fix_table;
  Table* fix_table2;

public:
  virtual void setUp();
  virtual void tearDown();
  void test_load_save();
  void test_closureAll();
  void test_getNumbers();
  void test_getNumbers2();
  void test_unionSets();
  void test_unionSets2();
  void test_unionSets3();
  void test_unionSets4();
  void test_SoE_union();
  void test_SoE_union2();
  void test_SoE_union3();
  void test_SoE_union4();
  void test_SoE_minus();
  void test_SoE_minus2();
  void test_SoE_minus3();
  void test_SoE_minus4();
  void test_setSup();
  void test_setInf();
  int generator_collec(string nom_table);
  int generator_collec2(string nom_table);
  void generator_closure(string nom_table);
  
  
};


#endif 
