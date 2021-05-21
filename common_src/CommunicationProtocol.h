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
    ssize_t _send_message(char* msg, int size);
    void _short_to_char(short int size,char* buffer);
    short int _char_to_short(char* buffer);

public:
    CommunicationProtocol(Socket socket);
    ssize_t communication_protocol_send_message(char* msg, int length);
    int communication_protocol_receive_size();
    ssize_t communication_protocol_receive_message(int length, char* buffer);
    ~CommunicationProtocol();
};

#endif
