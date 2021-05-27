#include "serverProtocol.h"
#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"

#include <iostream>
#include <vector>

Server_Protocol:: Server_Protocol(GameContainer* games):token(){
    this->gc = games;
}

void Server_Protocol:: init(const Socket& socket){
   this->socket = socket;
}

void Server_Protocol:: start_communication_protocol(){
    this->comm.init(std::move(this->socket));
}

void Server_Protocol:: set_token(const char& token){
    this->token = token;
}

void Server_Protocol:: select_execution_mode(){
    int bytes_received = 0;
    std::vector<char> mode(2);
    
    bytes_received = get_execution_mode(mode.data());

    while (bytes_received > 0){
        if ( strcmp(mode.data(),CREAR_KEY) == 0){
            receive_create_command();
        }else if ( strcmp(mode.data(),LISTAR_KEY) == 0){
            receive_list_command();
        }else if ( strcmp(mode.data(),UNIRSE_KEY) == 0){
            receive_join_command();
        }else if ( strcmp(mode.data(),JUGAR_KEY) == 0){
            receive_play_command();
        }
        bytes_received = get_execution_mode(mode.data());
    }
}

void Server_Protocol:: receive_join_command(){
    set_token(GUEST_TOKEN);
    int bytes_received(0);
    uint16_t game_name_size(0);
    game_name_size = this->comm.receive_size(&game_name_size);
    
    std::vector<char> message(game_name_size+1);
    bytes_received = comm.receive_message(game_name_size,message.data());

    if( bytes_received > 0)
        this->game.set_name(message.data());


}

void Server_Protocol:: receive_create_command(){
    set_token(HOST_TOKEN);
    int bytes_received(0);
    
    uint16_t game_name_size(0);
    game_name_size = this->comm.receive_size(&game_name_size);
    
    std::vector<char> message(game_name_size+1);
    bytes_received = comm.receive_message(game_name_size,message.data());

    if( bytes_received > 0){
        this->gc->create_new_game(message.data());
        this->game.set_name(message.data());
    }
    
}

void Server_Protocol:: receive_list_command(){
    std::string all_games_name("");
    all_games_name = this->gc->get_all_values();
    
    this->comm.send_size((int)all_games_name.length());
    this->comm.send_message(all_games_name.c_str(),all_games_name.length());
}

void Server_Protocol::receive_play_command(){
    int bytes_received = 0;
    std::vector<char> message(2);
    bytes_received = comm.receive_message(1,message.data());

    if( bytes_received > 0){
        try{
            makePlay(message.data(),this->game.get_name());
            check_game_status(this->game.get_name());
            send_board(this->game.get_name());
        } catch( GameFinishedException &error ){
            send_board_with_message(this->game.get_name());
        }
    }
}

void Server_Protocol:: check_game_status(const std::string& game_name){
    this->gc->check_game_status(game_name);
}

void Server_Protocol:: send_board(const std::string& game_name){
    std::string board("");
    board = this->gc->get_board(game_name);

    this->comm.send_size((int)board.length());
    this->comm.send_message(board.c_str(),board.length());
}

void Server_Protocol:: send_board_with_message(const std::string& game_name){
    std::string board("");
    board = this->gc->get_board(game_name);
    board += "\nFelicitaciones! Ganaste! \n";

    this->comm.send_size((int)board.length());
    this->comm.send_message(board.c_str(),board.length());
}

int Server_Protocol::get_execution_mode(char* mode){
    int bytes_received = 0;
    bytes_received = comm.receive_message(1,mode);
    return bytes_received;
}

void Server_Protocol:: makePlay
(const char* message, const std::string& game_name){
    unsigned char aux = 15; //0x0F
    unsigned char aux2 = 48; //0x30

    int column = message[0] >> 4;
    
    int row = message[0] & aux;
    
    column = (column | aux2)-48;
    row = (row | aux2)-48;

    this->gc->make_play(this->token,column,row,game_name);
}

Server_Protocol:: ~Server_Protocol(){}
