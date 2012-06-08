/* 
 * File:   MilKInterface.h
 * Author: hardion
 *
 * Created on May 24, 2012, 10:48 AM
 */
#ifndef MILKINTERFACE_H
#define	MILKINTERFACE_H

#include <string>
namespace milk {

  enum State {
    INIT, LOCALE, OFF, STANDBY, ON, RUNNING, ERROR
  };

  class MilKInterface {
  public:
    /*virtual MilKInterface(std::string ip, int port);*/
    /*virtual MilKInterface(const MilKInterface& orig)=0;*/
    //virtual ~MilKInterface() = 0;

    /** Attributes **/
    virtual int get_current() = 0;
    virtual int get_current_set() = 0;
    virtual int get_current_accuracy() = 0;

    virtual int get_field() = 0;
    virtual int get_field_set() = 0;
    virtual int get_field_accuracy() = 0;

    virtual int set_current(int new_value) = 0;
    virtual int set_field(int new_value) = 0;

    /* Configuration */
    virtual std::string get_ip() = 0;
    virtual unsigned short get_port() = 0;
    
    // State of the device composed by the information from
    // STATUS_RTIME
    virtual State get_state() = 0;

    // Status of the device (from READ_STATUS1)
    // A complete description of the current status of the device
    virtual std::string get_status() = 0;

    /** Commands **/
    virtual void on() = 0;
    virtual void standby() = 0;
    virtual void off() = 0;
    virtual void locale() = 0;
    virtual void remote() = 0;
    
    // Stop any process
    // This command doesn't change the mode of regulation
    virtual void stop() = 0;
    

  private:

  };
}


#endif	/* MILKINTERFACE_H */

