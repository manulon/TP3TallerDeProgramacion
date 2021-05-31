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

TaTeTi* ProtectedMap:: add_new_game(TaTeTi* game){
    this->internal[game->get_name()] = game;
    return game;
}

TaTeTi* ProtectedMap::get_game(const std::string& key){
    return this->internal.at(key);
}

ProtectedMap:: ~ProtectedMap() {
    for (auto &element : internal) {
        delete element.second;
	}
}
