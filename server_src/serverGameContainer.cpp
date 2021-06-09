#include "serverGameContainer.h"
#include <iostream>
#include <string>

GameContainer:: GameContainer():
game_finished(false){}

bool GameContainer:: contains(const std::string& key) {
    return this->internal.find(key) != this->internal.end();
}

TaTeTi* GameContainer:: create_new_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        TaTeTi* game = new TaTeTi(key);
        this->internal[key] = game;
        return game;
    }
    return NULL;
}

std::string GameContainer::get_all_values(){
    std::unique_lock<std::mutex> lk(this->m);
    std::string all_games_name("Partidas : \n");
    for (auto& element: internal){
        all_games_name += ("- " + element.second->get_name() + "\n");
    }
    return all_games_name;
}

TaTeTi* GameContainer::get_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    return this->internal.at(key);
}

GameContainer:: ~GameContainer(){
    for (auto &element : internal) {
        delete element.second;
	}
}
