/* 
 * File:   MilKMock.h
 * Author: hardion
 *
 * Created on May 24, 2012, 1:35 PM
 */

#ifndef MILKMOCK_H
#define	MILKMOCK_H

#include "MilKInterface.h"
namespace milk {

#define CURRENT_ACCURACY 0.01
#define FIELD_ACCURACY 0.00001

  enum MockInit {
    TEST_STATELESS
  };

  class MilKMock : public MilKInterface {
  public:

    MilKMock(std::string ip, unsigned short port);

    /* Exist only for the test*/
    MilKMock(std::string ip, unsigned short port, MockInit mode);

    MilKMock(const MilKMock& orig);

    virtual ~MilKMock();
	int openconnection(char command[256]) //open & close connection each time a command is sent
	{
		int sockfd, portno, n;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		//const char *argv[]= {"192.168.1.234"};
		const char *argv[]= {"127.0.0.1"};
		char buffer[256];
		portno = 1234;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
			perror("ERROR opening socket");
		server = gethostbyname(argv[0]);
		if (server == NULL) {
			fprintf(stderr,"ERROR, no such host\n");
		    exit(0);
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr, 
			 (char *)&serv_addr.sin_addr.s_addr,
			 server->h_length);
		serv_addr.sin_port = htons(portno);
		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
			perror("ERROR connecting");
		sprintf(buffer,"%s",command);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			 perror("ERROR writing to socket");
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
			 perror("ERROR reading from socket");
		printf("%s\n",buffer);
		sprintf(command,"%s",buffer);
		close(sockfd);
		return 0;
		
		}
    /** Attributes **/
    int get_current() {
		char command[256];
		sprintf(command,"%s","READ_CURRENT");
      openconnection(command);
      current= atof(command);
      return current;
    }

    int get_current_set() {
		char command[256];
		sprintf(command,"%s","READ_CURRSET");
      openconnection(command);
      current_set= atof(command);
      return current_set;
    }

    int set_current(int new_value) {
      if (state == STANDBY) {
        current_set = new_value;
      } else if (state == ON) {
        current_set = new_value;
        state = RUNNING;
      }

      return current_set;
    }

    int get_field() {
		char command[256];
		sprintf(command,"%s","READMAGFIELD");
      openconnection(command);
      field= atof(command);
      return field;
    }

    int get_field_set() {
		char command[256];
		sprintf(command,"%s","READ_FLD_SET");
      openconnection(command);
      field_set= atof(command);
      return field_set;
    }

    int set_field(int new_value) {
      if (state == STANDBY) {
        field_set = new_value;
      } else if (state == ON) {
        field_set = new_value;
        state = RUNNING;
      }

      return field_set;
    }

    /* Configuration */
    virtual std::string get_ip() {
      return ip;
    }

    virtual unsigned short get_port() {
      return port;
    }


    // State of the device composed by the information from
    // STATUS_RTIME

    virtual State get_state() {

      if (state == RUNNING) {
        // Simulate a movement
        State current_state = ON;
        if (current < current_set * (1 - CURRENT_ACCURACY)) {
          current += current_set*CURRENT_ACCURACY;
          current_state = RUNNING;
        } else if (current > current_set * (1 + CURRENT_ACCURACY) + CURRENT_ACCURACY) {
          current -= current*CURRENT_ACCURACY;
          current_state = RUNNING;
        } else {
          current = current_set;
        }

        // Simulate a movement
        State field_state = ON;
        if (field < field_set * (1 - FIELD_ACCURACY)) {
          field += field_set*FIELD_ACCURACY;
          field_state = RUNNING;
        } else if (field > field_set * (1 + FIELD_ACCURACY) + FIELD_ACCURACY) {
          field -= field*FIELD_ACCURACY;
          field_state = RUNNING;
        } else {
          field = field_set;
        }

        state = (current_state >= field_state ? current_state : field_state);

      }
      return state;
    }

    // Status of the device (from READ_STATUS1)

    virtual std::string get_status() {
      return "STATXXXXXXXX";
    }

    /** Commands **/
    void on() {
      if (state == OFF || state == STANDBY) {
        state = ON;
      }
    }

    void off() {
      if (state == ON || state == STANDBY) {
        state = OFF;
      }

    }

    void stop() {
      if (state == RUNNING) {
        state = ON;
      }

    }

    void standby() {
      if (state == ON) {
        state = STANDBY;
      }
    }

    void locale() {
      remote_state = state;
      state = LOCALE;
    }

    void remote() {
      state = remote_state;
    }

    virtual int get_current_accuracy() {
      return CURRENT_ACCURACY;
    }

    virtual int get_field_accuracy() {
      return FIELD_ACCURACY;
    }


  private:
    /*int*/ double current;
    int current_set;
    /*int*/ double field;
    int field_set;
    State state;
    State remote_state; // Use only to keep the state when going to locale state
    std::string ip;
    unsigned short port;

  };
}
#endif	/* MILKMOCK_H */

