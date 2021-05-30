#include "serverProtectedMap.h"
#include <iostream>

ProtectedMap:: ProtectedMap() {}

bool ProtectedMap:: contains(const std::string& key) {
    return this->internal.find(key) != this->internal.end();
}

void ProtectedMap:: set_name(const std::string& key){
    this->internal[key]->set_name(key);
}

std::string ProtectedMap::get_name(const std::string& key){
    return this->internal[key]->get_name();
}

std::string ProtectedMap::get_all_values(){
    std::string all_games_name("Partidas : \n");
    for (auto& element: internal){
        all_games_name += ("- " + element.second->get_name() + "\n");
    }
    return all_games_name;
}

void ProtectedMap:: make_play(const std::string& key,
const char& token, const unsigned char& row,
const unsigned char& column){
    this->internal.at(key)->set_new_position(token,column,row);
}

std::string ProtectedMap::get_board(const std::string& game_name){
    return this->internal.at(game_name)->get_board();
}

void ProtectedMap:: check_game_status
(const std::string& game_name,const char& token,std::string& msg){
    this->internal.at(game_name)->check_game_status(token,msg);
}

bool ProtectedMap:: game_already_start(const std::string& key){
    return this->internal.at(key)->game_already_start();
}

void ProtectedMap:: game_started(const std::string& key){
    this->internal.at(key)->start_game();
}

void ProtectedMap:: notify_winner(const std::string& key){
    this->internal.at(key)->notify_winner();
}

std::string ProtectedMap::get_initial_board(const std::string& game_name){
    return this->internal.at(game_name)->get_initial_board();
}

void ProtectedMap:: add_new_game(TaTeTi* game){
    this->internal[game->get_name()] = game;
}

TaTeTi* ProtectedMap::get_game(const std::string& key){
    return this->internal.at(key);
}

ProtectedMap:: ~ProtectedMap() {}
