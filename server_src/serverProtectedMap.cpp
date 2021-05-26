#include "serverProtectedMap.h"
#include <iostream>

ProtectedMap:: ProtectedMap() {}

bool ProtectedMap:: contains(const std::string& key) {
    return this->internal.find(key) != this->internal.end();
}

void ProtectedMap:: set_name(const std::string& key){
    this->internal[key].set_name(key);
}

std::string ProtectedMap::get_name(const std::string& key){
    return this->internal[key].get_name();
}

std::string ProtectedMap::get_all_values(){
    std::string all_games_name("Partidas : \n");
    for (auto& element: internal){
        all_games_name += ("- " + element.second.get_name() + "\n");
    }
    return all_games_name;
}

void ProtectedMap:: make_play(const std::string& key,
const char& token, const unsigned char& row,
const unsigned char& column){
    this->internal.at(key).set_new_position(token,column,row);
}

std::string ProtectedMap::get_board(const std::string& game_name){
    return this->internal.at(game_name).get_board();
}

void ProtectedMap:: check_game_status(const std::string& game_name){
    this->internal.at(game_name).check_game_status();
}

ProtectedMap:: ~ProtectedMap() {}