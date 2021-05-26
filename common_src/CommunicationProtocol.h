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
    void _short_to_char(const int& size,char* buffer);
    int _char_to_short(const char* buffer);

public:
    CommunicationProtocol();
    CommunicationProtocol(const Socket& socket);
    void init(const Socket& socket);
    ssize_t send_message(const char* msg,const int& length);
    ssize_t send_size(int size);
    ssize_t receive_message(const int& length, char* buffer);
    int receive_size();
    ~CommunicationProtocol();
};

#endif
