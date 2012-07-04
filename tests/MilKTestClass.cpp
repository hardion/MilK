/*
 * File:   MilKTestClass.cpp
 * Author: hardion
 *
 * Created on May 24, 2012, 11:52:35 AM
 */
#include "MilKTestClass.h"
#include "MilKInterface.h"
#include "MilKMock.h"

using namespace milk;

CPPUNIT_TEST_SUITE_REGISTRATION(MilKTestClass);

void MilKTestClass::test_INIT_state() {
  // TEST INIT
  // Maybe there is an INIT state, maybe not
  // In this case, we can perform a performance test
  // SPEC : The device have to start between X and Y
  // Otherwise comment these lines above
  State actual = milK->get_state();
  CPPUNIT_ASSERT_EQUAL(INIT, actual);

}

/**
 * TEST RUNNING State
 * SPEC : Setting a physical attribute change the state to RUNNING 
 * EXPECTED : the RUNNING state finish with ON State
 * This depends on the delay of the action : 
 * - No physical action = NO RUNNING STATE
 * - Otherwise = RUNNING STATE from the setting of the current to the end of the regulation
 */
void MilKTestClass::test_RUNNING_state() {
  State actual;
  milK->on();

  // Change a physical attribute
  milK->set_current(EXPECTED_CURRENT); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(RUNNING, milK->get_state());

  // The output of RUNNING State is ON or ERROR
  this->waitWhileState(RUNNING);
  actual = milK->get_state();
  CPPUNIT_ASSERT((actual == ON) || (actual == ERROR));

  // The Same for field attribute
  milK->set_field(EXPECTED_FIELD); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(RUNNING, milK->get_state());
  this->waitWhileState(RUNNING);
  actual = milK->get_state();
  CPPUNIT_ASSERT((actual == ON) || (actual == ERROR));

}

/**
 * TEST ERROR State
 * SPEC : ???
 * EXPECTED : ???
 * 
 */
void MilKTestClass::test_ERROR_state() {

}

/**
 * TEST Stateless behavior
 * SPEC : The state is given by the underline device, not the MilK library
 * EXPECTED : After change the state of the device, a delete/recreate have to return the same state
 * 
 */
void MilKTestClass::testStateless() {

  milK->on();
  CPPUNIT_ASSERT_EQUAL(ON, milK->get_state());

  // The heart of the test
  delete milK;
  milK = new MilKMock(IP, PORT, TEST_STATELESS); // !!!! For real implementation replace with new MilKImpl()
  CPPUNIT_ASSERT_EQUAL(ON, milK->get_state());

}

/**
 * TEST the written part of the current
 * SPEC : The written part always return the last allowed setpoint
 * EXPECTED : The method get_current_set() return the last argument of set_current (in normal condition)
 * 
 */
void MilKTestClass::testGet_current_set() {
  milK->on();

  milK->set_current(EXPECTED_CURRENT);
  CPPUNIT_ASSERT_EQUAL(EXPECTED_CURRENT, milK->get_current_set());
}

/**
 * TEST the current accuracy
 * SPEC : The value after the regulation is around the setpoint defined by the accuracy
 * EXPECTED : A correct value of current after change is obtained after a RUNNING state
 * 
 */
void MilKTestClass::testSet_current() {
  milK->on();

  // TEST the current accuracy
  milK->set_current(EXPECTED_CURRENT);
  this->waitWhileState(RUNNING);
  double precision = milK->get_current_accuracy();
  double precision_error = milK->get_current() / milK->get_current_set();
  CPPUNIT_ASSERT(precision_error >= 1 - precision);
  CPPUNIT_ASSERT(precision_error <= 1 + precision);

}

/**
 * TEST the written part of the field
 * SPEC : The written part always return the last allowed setpoint
 * EXPECTED : The method get_field_set() return the last argument of set_field (in normal condition)
 * 
 */
void MilKTestClass::testGet_field_set() {
  milK->on();

  milK->set_field(EXPECTED_FIELD);
  CPPUNIT_ASSERT_EQUAL(EXPECTED_FIELD, milK->get_field_set());
}

/**
 * TEST the field accuracy
 * SPEC : The value after the regulation is around the setpoint defined by the accuracy
 * EXPECTED : A correct value of field after change is obtained after a RUNNING state
 * 
 */
void MilKTestClass::testSet_field() {
  milK->on();

  // TEST the field accuracy
  milK->set_field(EXPECTED_FIELD);
  this->waitWhileState(RUNNING);
  double precision = milK->get_field_accuracy();
  double precision_error = milK->get_field() / milK->get_field_set();
  CPPUNIT_ASSERT(precision_error >= 1 - precision);
  CPPUNIT_ASSERT(precision_error <= 1 + precision);

}

/**
 * TEST Not allowed to change the physical attribute (field or current) while RUNNING 
 * SPEC : While RUNNING, it is not allowed to change the physical attribute
 * EXPECTED : A correct value of current/field after change is obtained after a RUNNING state
 * 
 */
void MilKTestClass::testSet_physical_attribute_while_RUNNING() {

  // TEST Not allowed to change the current while RUNNING 
  milK->on();
  milK->set_current(EXPECTED_CURRENT);
  if (RUNNING == milK->get_state()) {
    milK->set_current(NOT_EXPECTED_CURRENT);
    CPPUNIT_ASSERT(NOT_EXPECTED_CURRENT != milK->get_current_set());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("TEST1",EXPECTED_CURRENT, milK->get_current_set());
    
  } else {
    CPPUNIT_ASSERT_MESSAGE("This unit test was not launch in good condition", false);

  }
  
this->waitWhileState(RUNNING);
milK->off();

  // TEST Not allowed to change the field while RUNNING 
  milK->on();
  milK->set_field(EXPECTED_FIELD);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("TEST2.1",EXPECTED_FIELD, milK->get_field_set());

  if (RUNNING == milK->get_state()) {
    milK->set_field(NOT_EXPECTED_FIELD);
    CPPUNIT_ASSERT(NOT_EXPECTED_FIELD != milK->get_field_set());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("TEST2",EXPECTED_FIELD, milK->get_field_set());

  } else {
    CPPUNIT_ASSERT_MESSAGE("This unit test was not launch in good condition", false);

  }

}

void MilKTestClass::testOn() {
  State expected = ON;

  // Force another state
  milK->off();

  // TEST ON State
  // SPEC : the command on ends with ON State
  // Delay max : 2 seconds
  milK->on();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());

  // SPEC : A call to on() when the state is already ON
  // TEST 2 times calling a on()
  milK->on(); // This should do nothing
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());


}

void MilKTestClass::testStop() {

  // Force another state
  milK->on();

  // TEST Stop Command
  // SPEC : the command stop stops the current and ends with ON State
  milK->set_current(EXPECTED_CURRENT); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(RUNNING, milK->get_state());
  milK->stop();
  CPPUNIT_ASSERT_EQUAL(ON, milK->get_state());
  CPPUNIT_ASSERT(milK->get_current() != milK->get_current_set());


  // TEST Stop Command
  // SPEC : the command stop stops the current and ends with ON State
  milK->set_field(EXPECTED_FIELD); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(RUNNING, milK->get_state());
  milK->stop();
  CPPUNIT_ASSERT_EQUAL(ON, milK->get_state());
  CPPUNIT_ASSERT(milK->get_field() != milK->get_field_set());
}

void MilKTestClass::testOff() {
  State expected = OFF;

  // Force another state
  milK->on();

  // TEST ON State
  // SPEC : the command on ends with OFF State
  // Delay max : 2 seconds
  milK->off();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());

  // SPEC : A call to on() when the state is already OFF, do nothing
  // TEST 2 times calling a on()
  milK->off(); // This should do nothing
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());

  // SPEC : 
  milK->off();
  CPPUNIT_ASSERT_EQUAL(0, milK->get_current());
  CPPUNIT_ASSERT_EQUAL(0, milK->get_field());

}

/**
 * TEST the Standby state and command
 * SPEC : While RUNNING, it is not allowed to change the physical attribute
 * EXPECTED : A correct value of current/field after change is obtained after a RUNNING state
 * 
 */
void MilKTestClass::testStandBy() {
  State expected = STANDBY;

  // TEST StandBy State from OFF
  // SPEC : the command standby ends with STANDBY State
  // Delay max : 2 seconds
  milK->off();
  milK->standby();
  CPPUNIT_ASSERT_EQUAL(OFF, milK->get_state());

  // TEST StandBy State from OFF
  // SPEC : the command standby ends with STANDBY State
  // Delay max : 2 seconds
  milK->on();
  milK->standby();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());

  // SPEC : A call to on() when the state is already OFF, do nothing
  // TEST 2 times calling a on()
  milK->standby();
  milK->standby(); // This should do nothing
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());

  // SPEC : The current is not regulated
  milK->on();
  milK->set_current(EXPECTED_CURRENT); // Modify if this value doesn't start a long action
  this->waitWhileState(RUNNING);
  milK->standby();
  milK->set_current(NOT_EXPECTED_CURRENT); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  //this->waitWhileState(RUNNING);
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  CPPUNIT_ASSERT(NOT_EXPECTED_CURRENT != milK->get_current());
  CPPUNIT_ASSERT(NOT_EXPECTED_CURRENT == milK->get_current_set());

  // SPEC : The field is not regulated
  milK->on();
  milK->set_field(EXPECTED_FIELD); // Modify if this value doesn't start a long action
  this->waitWhileState(RUNNING);
  milK->standby();
  milK->set_field(NOT_EXPECTED_FIELD); // Modify if this value doesn't start a long action
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  //this->waitWhileState(RUNNING);
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  CPPUNIT_ASSERT(NOT_EXPECTED_FIELD != milK->get_field());
}

void MilKTestClass::testLocaleRemote() {
  State expected = LOCALE;

  // TEST StandBy State from ON
  // SPEC : the command standby ends with LOCALE State
  // Delay max : 2 seconds
  milK->on();
  milK->locale();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  milK->remote();
  CPPUNIT_ASSERT_EQUAL(ON, milK->get_state());

  // TEST StandBy State from OFF
  // SPEC : the command standby ends with LOCALE State
  // Delay max : 2 seconds
  milK->off();
  milK->locale();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  milK->remote();
  CPPUNIT_ASSERT_EQUAL(OFF, milK->get_state());

  // TEST StandBy State from STANDBY
  // SPEC : the command standby ends with LOCALE State
  // Delay max : 2 seconds
  milK->on();
  milK->standby();
  milK->locale();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  milK->remote();
  CPPUNIT_ASSERT_EQUAL(STANDBY, milK->get_state());
  
  
  // SPEC : Not allowed to set the current
  milK->on();
  milK->locale();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  milK->set_current(NOT_EXPECTED_CURRENT);
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  CPPUNIT_ASSERT(NOT_EXPECTED_CURRENT != milK->get_current_set());

  // SPEC : Not allowed to set the field
  milK->on();
  milK->locale();
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  milK->set_field(NOT_EXPECTED_FIELD);
  CPPUNIT_ASSERT_EQUAL(expected, milK->get_state());
  CPPUNIT_ASSERT(NOT_EXPECTED_FIELD != milK->get_field_set());

}

