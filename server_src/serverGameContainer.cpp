#include "serverGameContainer.h"
#include <iostream>
#include <string>

GameContainer:: GameContainer():
game_finished(false){}

bool GameContainer:: contains(const std::string& key) {
    return this->map.contains(key);
}

void GameContainer:: create_new_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        this->map.add_new_game(new TaTeTi(key));
    }
}

std::string GameContainer::get_all_values(){
    std::unique_lock<std::mutex> lk(this->m);
    return this->map.get_all_values();
}

void GameContainer:: add_new_game(TaTeTi* game){
    std::unique_lock<std::mutex> lk(this->m);
    this->map.add_new_game(game);
}

TaTeTi* GameContainer::get_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    return this->map.get_game(key);
}

GameContainer:: ~GameContainer(){}
