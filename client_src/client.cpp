#include "client.h"

Client:: Client(char const *argv[]){
    this->hostname = argv[1];
    this->servicename = argv[2];
}

void Client:: init_connection(){
    this->socket.socket_connect(this->hostname,this->servicename);
}

void Client:: communicate_with_server(){
    CommunicationProtocol commu(std::move(this->socket));
    
    std::string line = "";
    std::getline(std::cin, line);
    
    if (line.find("jugar") != std::string::npos){
        std::string line_to_send = "p";
        std::string jugar = "jugar";

        size_t p = -1;

        std::string tempWord = jugar + " ";
        while ((p = line.find(jugar)) != std::string::npos)
            line.replace(p, tempWord.length(), "");
  
        tempWord = " " + jugar;
        while ((p = line.find(jugar)) != std::string::npos)
            line.replace(p, tempWord.length(), "");


        line_to_send = line_to_send + line;
        commu.send_message(line_to_send.c_str(),line_to_send.length());
    }
}

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

Client:: ~Client(){}
