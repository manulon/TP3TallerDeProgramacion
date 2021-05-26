#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

#include "Socket.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

class CommunicationProtocol{

    Socket socket;

private:
    ssize_t _send_message(const char* msg,const int& size);

public:
    CommunicationProtocol();
    CommunicationProtocol(const Socket& socket);
    void init(const Socket& socket);
    ssize_t send_message(const char* msg,const int& length);
    ssize_t send_size(uint16_t size);
    ssize_t receive_message(const int& length, char* buffer);
    int receive_size(uint16_t* size);
    ~CommunicationProtocol();
};

#endif
