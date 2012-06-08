/* 
 * File:   MilKMock.cpp
 * Author: hardion
 * 
 * Created on May 24, 2012, 1:35 PM
 */

#include "MilKMock.h"

namespace milk {

  MilKMock::MilKMock(std::string ip, unsigned short port) {
    current = 0;
    current_set = 0;
    field = 0;
    field_set = 0;
    state = OFF;
  }
  
  MilKMock::MilKMock(std::string ip, unsigned short port, MockInit mode){
    MilKMock(ip, port);
    if(mode == TEST_STATELESS){
      state = ON;     
    }
  }

  MilKMock::MilKMock(const MilKMock& orig) {
    this->current = orig.current;
    this->current_set = orig.current_set;
    this->field = orig.field;
    this->field_set = orig.field_set;
    this->state = orig.state;
  }

  MilKMock::~MilKMock() {
    
  }


}
