#include "clientProtocol.h"
#include <iostream>

Client_Protocol:: Client_Protocol(){}

void Client_Protocol:: init(const Socket& socket){
   this->socket = socket;
}
    
    
void Client_Protocol:: start_communication_protocol(){
    std::string line = "";
    std::getline(std::cin, line);

    this->comm.init(std::move(this->socket));

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
        this->comm.send_message(line_to_send.c_str(),line_to_send.length());
    }
}
    
    
    
Client_Protocol:: ~Client_Protocol(){}

