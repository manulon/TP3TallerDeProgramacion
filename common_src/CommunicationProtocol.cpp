#include "CommunicationProtocol.h"

CommunicationProtocol:: CommunicationProtocol(Socket socket){
    this->socket = socket;
}

ssize_t CommunicationProtocol:: send_message(char* msg, int length){
    ssize_t total_bytes_sent = 0;
    _send_size(length);
    _send_message(msg,length);
    return total_bytes_sent;
}

ssize_t CommunicationProtocol:: _send_size(int size){
    int remaining_bytes = 2;       
    int total_bytes_sent = 0;
    char buffer[2];

    _short_to_char(size,buffer);

    while (total_bytes_sent < 2) {
        ssize_t bytes = send(this->socket.fd, 
                            &buffer[total_bytes_sent],
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

ssize_t CommunicationProtocol:: _send_message(char* msg, int size){
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

int CommunicationProtocol:: receive_size(){
    char buffer[2] = "";                    
    int remaining_bytes = 2;
    int total_bytes_received = 0;
    while (total_bytes_received < 2) {
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

    int size = _char_to_short(buffer);
    return size;
}

ssize_t CommunicationProtocol:: receive_message(int length, char* buffer){
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

void CommunicationProtocol:: _short_to_char(short int size,char* buffer){
    buffer[0] = (size >> 8) & 0xff;
    buffer[1] = size & 0xff;
}

short int CommunicationProtocol:: _char_to_short(char* buffer){  
    short int pshort;

    pshort = (buffer[0] << 8) | buffer[1];
    
    return pshort;
}

CommunicationProtocol:: ~CommunicationProtocol(){}
