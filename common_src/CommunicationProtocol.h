#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

#include "Socket.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

class CommunicationProtocol{
    Socket* socket;

public:
    CommunicationProtocol();
    ~CommunicationProtocol();
    explicit CommunicationProtocol(Socket* socket);   
    
    //Envia el mensaje recibido por parametro.
    ssize_t send_message(const char* msg,const int& length);
    
    //Envia el size recibido por parametro.
    ssize_t send_size(uint16_t size);
    
    //Recibe un mensaje de largo length.
    ssize_t receive_message(const int& length, char* buffer);
    
    //Recibe el tamaño de un mensaje
    int receive_size(uint16_t* size);
};

#endif
