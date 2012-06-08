/*
 * File:   MilKTest.cpp
 * Author: hardion
 *
 * Created on May 24, 2012, 11:36:42 AM
 */

#include "MilKTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MilKTest);

MilKTest::MilKTest() {
}

MilKTest::~MilKTest() {
}

void MilKTest::setUp() {
}

void MilKTest::tearDown() {
}

void MilKTest::testMethod() {
  CPPUNIT_ASSERT(true);
}

void MilKTest::testFailedMethod() {
  CPPUNIT_ASSERT(false);
}

