#include "client.h"

Client:: Client(){}

void Client:: init_connection(Socket socket){
    this->socket.socket_connect(this->hostname,this->servicename);
}

void Client:: communicate_with_server(){}

void Client:: set_message_length(int len){
    this->message_length = len;
}

void Client:: set_message(char* msg){
    this->message = 
        (char*)calloc(this->message_length+1, sizeof(char));
    
    strncpy((char*)this->message,(char*)msg,this->message_length);
    this->message[this->message_length] = 0;
}

char* Client:: get_message(){
    return this->message;
}

int Client:: get_message_length(){
    return this->message_length;
}