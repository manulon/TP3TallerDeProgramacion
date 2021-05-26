#include "CommunicationProtocol.h"
#include <iostream>

CommunicationProtocol:: CommunicationProtocol(){}

CommunicationProtocol:: CommunicationProtocol(const Socket& socket){
    this->socket = socket;
}

void CommunicationProtocol:: init(const Socket& socket){
    this->socket = socket;
}

ssize_t CommunicationProtocol:: send_message(const char* msg,const int& length){
    ssize_t total_bytes_sent = 0;
    _send_message(msg,length);
    return total_bytes_sent;
}

ssize_t CommunicationProtocol:: _send_message(const char* msg,const int& size){
    int remaining_bytes = size;
    int total_bytes_sent = 0;

    while (total_bytes_sent < size) {
        ssize_t bytes = send(this->socket.fd, 
                            &msg[total_bytes_sent], 
                             remaining_bytes, MSG_NOSIGNAL);
    
        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

ssize_t CommunicationProtocol:: receive_message(const int& length, char* buffer){
    if (length == 0){ return 0; }
    int remaining_bytes = length;
    int total_bytes_received = 0;

    while (total_bytes_received < length) {
        ssize_t bytes = recv(this->socket.fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);
        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_received;
}

ssize_t CommunicationProtocol:: send_size(uint16_t size){
    int remaining_bytes = 2;       
    int total_bytes_sent = 0;

    size = htons(size);

    while (total_bytes_sent < 2) {
        ssize_t bytes = send(this->socket.fd, 
                            (char*) &size,
                            remaining_bytes, MSG_NOSIGNAL);

        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

int CommunicationProtocol:: receive_size(uint16_t* size){
    int remaining_bytes = 2;
    int total_bytes_received = 0;
    while (total_bytes_received < 2) {
        ssize_t bytes = recv(this->socket.fd,(char*)size,
                        remaining_bytes, 0);
        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;

        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    int final_size = 0;
    final_size = ntohs(*size);
    return final_size;
}

CommunicationProtocol:: ~CommunicationProtocol(){}
