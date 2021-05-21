#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

#include "Socket.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

class CommunicationProtocol{

    Socket socket;

private:
    ssize_t _send_size(int size);
    ssize_t _send_message(const char* msg, int size);
    void _short_to_char(short int size,char* buffer);
    short int _char_to_short(const char* buffer);

public:
    CommunicationProtocol(const Socket& socket);
    ssize_t send_message(const char* msg, int length);
    int receive_size();
    ssize_t receive_message(int length, char* buffer);
    ~CommunicationProtocol();
};

#endif
