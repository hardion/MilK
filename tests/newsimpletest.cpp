/* 
 * File:   newsimpletest.cpp
 * Author: hardion
 *
 * Created on May 24, 2012, 11:49:00 AM
 */

#include <stdlib.h>
#include <iostream>
#include "MilKInterface.h"

/*
 * Simple C++ Test Suite
 */

void testGet_state() {
  MilKInterface milKInterface;
  State result = milKInterface.get_state();
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testGet_state (newsimpletest) message=error message sample" << std::endl;
  }
}

void testSet_current() {
  int new_value;
  MilKInterface milKInterface;
  int result = milKInterface.set_current(new_value);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testSet_current (newsimpletest) message=error message sample" << std::endl;
  }
}

void testSet_field() {
  int new_value;
  MilKInterface milKInterface;
  int result = milKInterface.set_field(new_value);
  if (true /*check result*/) {
    std::cout << "%TEST_FAILED% time=0 testname=testSet_field (newsimpletest) message=error message sample" << std::endl;
  }
}

int main(int argc, char** argv) {
  std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% testGet_state (newsimpletest)" << std::endl;
  testGet_state();
  std::cout << "%TEST_FINISHED% time=0 testGet_state (newsimpletest)" << std::endl;

  std::cout << "%TEST_STARTED% testSet_current (newsimpletest)" << std::endl;
  testSet_current();
  std::cout << "%TEST_FINISHED% time=0 testSet_current (newsimpletest)" << std::endl;

  std::cout << "%TEST_STARTED% testSet_field (newsimpletest)" << std::endl;
  testSet_field();
  std::cout << "%TEST_FINISHED% time=0 testSet_field (newsimpletest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}

