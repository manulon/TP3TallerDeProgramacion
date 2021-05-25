#include "clientProtocol.h"
#include <iostream>
#include <sstream> 

Client_Protocol:: Client_Protocol(){}

void Client_Protocol:: init(const Socket& socket){
   this->socket = socket;
}
    
    
void Client_Protocol:: start_communication_protocol(){
    std::cout<<"Ingrese uno de los comandos designados por favor: "<<std::endl;
    std::string line = "";
    std::getline(std::cin, line);

    select_execution_mode(line);

}

void Client_Protocol:: select_execution_mode(std::string line){
    std::string mode = "";
    mode = get_execution_mode(line);

    if ( mode == "crear"){
        mode_create(line);
    }else if (mode == "listar"){

    }else if (mode == "unirse"){

    }else if (mode == "jugar"){
        mode_play(line);
    }else{
        //hel_mode()
    }
}
    
void Client_Protocol:: mode_play(std::string line){
    bool keep_reading_from_cin = true;

    while(keep_reading_from_cin){
        if (line != "q"){
            unsigned char row = line[line.length()-1];
            unsigned char column = line[line.length()-2];

            column = column << 4;

            unsigned char aux = 15; // 0x0F
            row = row & aux;

            unsigned char final = column | row;

            this->comm.init(std::move(this->socket));

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
            
            std::getline(std::cin, line);
            
        }else{
            keep_reading_from_cin = false;
        }
    }
}

void Client_Protocol:: mode_create(std::string line){

}

std::string Client_Protocol:: get_execution_mode(std::string line){
    std::istringstream iss(line);
    std::string word = "";
    iss >> word;
    return word;
}

Client_Protocol:: ~Client_Protocol(){}

