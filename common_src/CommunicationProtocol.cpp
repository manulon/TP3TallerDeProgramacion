#include "CommunicationProtocol.h"
#include <iostream>
#include <arpa/inet.h>

CommunicationProtocol:: CommunicationProtocol(){}

CommunicationProtocol:: CommunicationProtocol(Socket* socket):
socket(socket){}

ssize_t CommunicationProtocol:: send_message(const char* msg,int length){
    return this->socket->socket_send(msg,length);
}

ssize_t CommunicationProtocol:: send_size(uint16_t size){
    size = htons(size);
    this->socket->socket_send((char*)&size,2);
    return 2;
}

ssize_t CommunicationProtocol:: receive_message
(int length, char* buffer){
    return this->socket->socket_receive(length,buffer);
}

int CommunicationProtocol:: receive_size(uint16_t* size){
    this->socket->socket_receive(2,(char*)size);
    return (int)ntohs(*size);
}

CommunicationProtocol:: ~CommunicationProtocol(){}
