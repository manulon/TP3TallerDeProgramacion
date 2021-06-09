#include "serverProtocol.h"
#include "TaTeTi.h"
#include "../common_src/GameFinishedException.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

Server_Protocol:: Server_Protocol(GameContainer* games,Socket* socket):
token(),final_game_msg(""),socket(socket),comm(this->socket),
game(nullptr),gc(games){}

void Server_Protocol:: set_token(const char& token){
    this->token = token;
}

int Server_Protocol:: select_execution_mode(){
    char mode(0);
    
    int bytes_received(get_execution_mode(mode));

    while (bytes_received > 0){
        if ( mode == CREAR_KEY ){
            receive_create_command();
        }else if ( mode == LISTAR_KEY ){
            receive_list_command();
        }else if ( mode == UNIRSE_KEY ){
            receive_join_command();
        }else if ( mode == JUGAR_KEY ){
            receive_play_command();
        }
        bytes_received = get_execution_mode(mode);
    }
    return bytes_received;
}

void Server_Protocol:: receive_join_command(){
    set_token(GUEST_TOKEN);

    uint16_t game_name_size(this->comm.receive_size(&game_name_size));
    
    std::vector<char> message(game_name_size,0);
   
    int bytes_received(comm.receive_message(game_name_size,message.data()));

    if (bytes_received > 0){
        std::ostringstream os;
        os.write(message.data(),game_name_size);
        std::string str(os.str());

        this->game = this->gc->get_game(str);
        send_board(this->game->get_name());
    }
}

void Server_Protocol:: receive_create_command(){
    set_token(HOST_TOKEN);

    uint16_t game_name_size(this->comm.receive_size(&game_name_size));
    
    std::vector<char> message(game_name_size,0);
    
    int bytes_received(comm.receive_message(game_name_size,message.data()));

    if (bytes_received > 0){
        std::ostringstream os;
        os.write(message.data(),game_name_size);
        std::string str(os.str());

        this->game = this->gc->create_new_game(str);
        
        std::string board(this->game->get_board());
        this->comm.send_size((int)board.length());
        this->comm.send_message(board.c_str(),board.length());
    }
}

void Server_Protocol:: receive_list_command(){
    std::string all_games_name(this->gc->get_all_values());
    
    this->comm.send_size((int)all_games_name.length());
    this->comm.send_message(all_games_name.c_str(),all_games_name.length());
}

void Server_Protocol::receive_play_command(){
    char message(0);

    int bytes_received(comm.receive_message(1,&message));

    if (bytes_received > 0){
        makePlay(message,this->game->get_name());
        send_board(this->game->get_name());
    }
}

void Server_Protocol:: send_board(const std::string& game_name){
        std::string board(this->game->get_board());
        
        this->game->check_game_status(this->token,this->final_game_msg);

        if (this->final_game_msg != "")
            this->game->notify_winner();

        board += this->final_game_msg;
      
        this->comm.send_size((int)board.length());
        this->comm.send_message(board.c_str(),board.length());  
}

int Server_Protocol::get_execution_mode(char& mode){   
    int bytes_received(0);
    bytes_received = comm.receive_message(1,&mode);
    return bytes_received;
}

void Server_Protocol:: makePlay
(char message, const std::string& game_name){
    this->game->set_new_position
        (this->token,decode_column(message),decode_row(message));
}

int Server_Protocol:: decode_column(char message){
    unsigned char aux2(0x30);

    int column(message >> 4);
    column = (column | aux2)-47;

    return column;
}

int Server_Protocol:: decode_row(char message){
    unsigned char aux(0x0F);
    unsigned char aux2(0x30); 

    int row(message & aux);
    row = (row | aux2)-47;

    return row;
}

Server_Protocol:: ~Server_Protocol(){}
