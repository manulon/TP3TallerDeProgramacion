#include "clientProtocol.h"
#include "../common_src/GameFinishedException.h"
#include <iostream>
#include <sstream> 
#include <vector>
#include <utility>

Client_Protocol:: Client_Protocol(){}

Client_Protocol:: Client_Protocol(Socket* socket):
socket(socket),comm(this->socket){}
       
void Client_Protocol:: start_communication_protocol(){
    bool keep_reading_from_cin = true;
    std::string line = "";

    std::getline(std::cin, line);
    while (keep_reading_from_cin){
        try{
            select_and_execute_mode(line);
            std::getline(std::cin, line);
        }catch(GameFinishedException& error){
            keep_reading_from_cin = false;
        }
    }
}

void Client_Protocol:: select_and_execute_mode(std::string& line){
    std::string mode(get_execution_mode(line));

    if (mode == CREAR_KEYWORD){
        mode_create(line);
    }else if (mode == LISTAR_KEYWORD){
        mode_list();
    }else if (mode == UNIRSE_KEYWORD){
        mode_join(line);
    }else if (mode == JUGAR_KEYWORD){
        mode_play(line);
    }
}

void Client_Protocol:: mode_join(const std::string& line){
    std::string game_name("");
    get_game_name(game_name,line);

    char key = UNIRSE_KEY;

    this->comm.send_message(&key,1);
    this->comm.send_size((int)(game_name.length()));
    this->comm.send_message(game_name.c_str(),game_name.length());    

    uint16_t board_size(this->comm.receive_size(&board_size));

    std::vector<char> board(board_size,0);

    int bytes_received(comm.receive_message(board_size,board.data()));
    
    if (bytes_received > 0){
        std::cout.write(board.data(),board_size);
    }   
}

void Client_Protocol:: mode_list(){
    char key = LISTAR_KEY;
    this->comm.send_message(&key,1);

    uint16_t size(this->comm.receive_size(&size));

    std::vector<char> all_games_name(size,0);
    int bytes_received(this->comm.receive_message(size,all_games_name.data()));
    
    if (bytes_received > 0)
        std::cout.write(all_games_name.data(),size);
}

void Client_Protocol:: mode_play(const std::string& line){
    unsigned char position(0);

    position = encode_position(line[line.length()-1],
                                     line[line.length()-3]);

    std::string str(1,position);

    char key = JUGAR_KEY;
    this->comm.send_message(&key,1);
    this->comm.send_message(str.c_str(),str.length());

    uint16_t size(this->comm.receive_size(&size));

    std::vector<char> board(size,0);
    int bytes_received(this->comm.receive_message(size,board.data()));

    if (bytes_received > 0)
        std::cout.write(board.data(),size);

    if (size != STANDARD_BOARD_SIZE)
        throw GameFinishedException();
}

unsigned char Client_Protocol:: encode_position
(unsigned char row, unsigned char column){
    column = (column-1) << 4;

    unsigned char aux = 0x0F; 
    row = (row-1) & aux;

    return (column | row);
}

void Client_Protocol:: mode_create(const std::string& line){
    std::string game_name("");
    get_game_name(game_name,line);
    char key = CREAR_KEY;

    this->comm.send_message(&key,1);
    this->comm.send_size((int)(game_name.length()));
    this->comm.send_message(game_name.c_str(),game_name.length());
    

    uint16_t board_size(this->comm.receive_size(&board_size));
    
    std::vector<char> board(board_size,0);
    int bytes_received(comm.receive_message(board_size,board.data()));

    if (bytes_received > 0){
        std::cout.write(board.data(),board_size);
    }   
}

std::string Client_Protocol:: get_execution_mode(const std::string& line){
    std::istringstream iss(line);
    std::string word = "";
    iss >> word;
    return word;
}

void Client_Protocol::get_game_name
(std::string& keyword,const std::string& line){
    std::stringstream ss(line);

    ss >> keyword;
    ss >> keyword;
}

Client_Protocol:: ~Client_Protocol(){}
