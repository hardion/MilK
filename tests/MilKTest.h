/*
 * File:   MilKTest.h
 * Author: hardion
 *
 * Created on May 24, 2012, 11:36:42 AM
 */

#ifndef MILKTEST_H
#define	MILKTEST_H

#include <cppunit/extensions/HelperMacros.h>

class MilKTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(MilKTest);

  CPPUNIT_TEST(testMethod);
  CPPUNIT_TEST(testFailedMethod);

  CPPUNIT_TEST_SUITE_END();

public:
  MilKTest();
  virtual ~MilKTest();
  void setUp();
  void tearDown();

private:
  void testMethod();
  void testFailedMethod();
};

#endif	/* MILKTEST_H */

