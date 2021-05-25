#include "clientProtocol.h"
#include <iostream>
#include <sstream> 

Client_Protocol:: Client_Protocol(){}

void Client_Protocol:: init(const Socket& socket){
   this->socket = socket;
}
       
void Client_Protocol:: start_communication_protocol(){
    std::cout<<"Ingrese uno de los comandos designados por favor: "<<std::endl;
    this->comm.init(std::move(this->socket));

    bool keep_reading_from_cin = true;
    std::string line = "";

    std::getline(std::cin, line);
    while(keep_reading_from_cin){
        if (line != "q"){
            select_execution_mode(line);
            std::getline(std::cin, line);
        }else{
            keep_reading_from_cin = false;
        }
    }
}

void Client_Protocol:: select_execution_mode(std::string& line){
    std::string mode = "";
    mode = get_execution_mode(line);

    if ( mode == CREAR_KEYWORD){
        mode_create(line);
    }else if (mode == LISTAR_KEYWORD){
        mode_list();
    }else if (mode == UNIRSE_KEYWORD){

    }else if (mode == JUGAR_KEYWORD){
        mode_play(line);
    }else{
        //help_mode()
    }
}

void Client_Protocol:: mode_list(){
    std::string key = LISTAR_KEY;
    this->comm.send_message(key.c_str(),key.length());
}

void Client_Protocol:: mode_play(std::string& line){
    unsigned char row = line[line.length()-1];
    unsigned char column = line[line.length()-2];

    column = column << 4;

    unsigned char aux = 15; // 0x0F
    row = row & aux;

    unsigned char final = column | row;

    std::string str(1,final);

    std::string key = JUGAR_KEY;
    this->comm.send_message(key.c_str(),key.length());
    this->comm.send_message(str.c_str(),str.length());
}

void Client_Protocol:: mode_create(std::string& line){
    std::string crear = CREAR_KEYWORD;

    size_t p = -1;

    std::string tempWord = crear + " ";
            
    while ((p = line.find(crear)) != std::string::npos)
        line.replace(p, tempWord.length(), "");
        
    tempWord = " " + crear;
    while ((p = line.find(crear)) != std::string::npos)
        line.replace(p, tempWord.length(), "");       

    
    std::string key = CREAR_KEY;

    this->comm.send_message(key.c_str(),key.length());
    this->comm.send_size((int)(line.length()));
    this->comm.send_message(line.c_str(),line.length());
}

std::string Client_Protocol:: get_execution_mode(const std::string& line){
    std::istringstream iss(line);
    std::string word = "";
    iss >> word;
    return word;
}

Client_Protocol:: ~Client_Protocol(){}

