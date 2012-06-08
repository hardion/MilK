/*
 * File:   MilKTestClass.h
 * Author: hardion
 *
 * Created on May 24, 2012, 11:52:35 AM
 */

#ifndef MILKTESTCLASS_H
#define	MILKTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

#include "MilKMock.h"

// Modify if this value doesn't start a long action
#define IP "127.0.0.1" 
#define PORT 65535 

// Modify if this value doesn't start a long action
#define EXPECTED_CURRENT 100 
#define NOT_EXPECTED_CURRENT 200 

// Modify if this value doesn't start a long action
#define EXPECTED_FIELD 2 
#define NOT_EXPECTED_FIELD -2

using namespace milk;

class MilKTestClass : public CPPUNIT_NS::TestFixture {
  
  CPPUNIT_TEST_SUITE(MilKTestClass);

  CPPUNIT_TEST(testGet_current_set);
  CPPUNIT_TEST(testGet_field_set);
  /*CPPUNIT_TEST(test_INIT_state);*/
  CPPUNIT_TEST(test_RUNNING_state);
  /*CPPUNIT_TEST(test_ERROR_state);*/
  CPPUNIT_TEST(testSet_current);
  CPPUNIT_TEST(testSet_field);
  CPPUNIT_TEST(testOn);
  CPPUNIT_TEST(testStandBy);
  CPPUNIT_TEST(testOff);
  CPPUNIT_TEST(testLocaleRemote);
  CPPUNIT_TEST(testStop);
  CPPUNIT_TEST(testStateless);
  CPPUNIT_TEST(testSet_physical_attribute_while_RUNNING);


  CPPUNIT_TEST_SUITE_END();

public:

  MilKTestClass() {
  }

  virtual ~MilKTestClass() {
  }

  void setUp() {
    milK = new MilKMock(IP, PORT);
  }

  void tearDown() {
    this->cleanMilK();
    delete milK;
  }

private:
  void testGet_current_set();
  void testGet_field_set();
  void testOn();
  void testOff();
  void testStop();
  void testSet_current();
  void testSet_field();
  void test_INIT_state();
  void test_RUNNING_state();
  void test_ERROR_state();
  void testStateless();
  void testSet_physical_attribute_while_RUNNING();
  void testStandBy();
  void testLocaleRemote();


  MilKInterface* milK;

  void cleanMilK() {
    // Clean Test
    this->waitWhileState(RUNNING);
    milK->set_current(0);
    this->waitWhileState(RUNNING);
    milK->set_field(0);
    this->waitWhileState(RUNNING);

  }

  void waitWhileState(State expected) {
    while (milK->get_state() == expected) {
      sleep(0.1);
    }
  }
  
};

#endif	/* MILKTESTCLASS_H */
