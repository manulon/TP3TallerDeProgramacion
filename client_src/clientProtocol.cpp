#include "clientProtocol.h"
#include <iostream>

Client_Protocol:: Client_Protocol(){}

void Client_Protocol:: init(const Socket& socket){
   this->socket = socket;
}
    
    
void Client_Protocol:: start_communication_protocol(){
    std::cout<<"Ingrese uno de los comandos designados por favor: "<<std::endl;
    std::string line = "";
    std::getline(std::cin, line);
  
    unsigned char row = line[line.length()-1];
    unsigned char column = line[line.length()-2];

    column = column << 4;

    unsigned char aux = 15; // 0x0F
    row = row & aux;

    unsigned char final = column | row;

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

        std::string str(1,final);

        line_to_send += str;

        this->comm.send_message(line_to_send.c_str(),line_to_send.length());
    }
}
    
    
    
Client_Protocol:: ~Client_Protocol(){}

