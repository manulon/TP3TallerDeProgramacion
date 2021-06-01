#include "serverGameContainer.h"
#include <iostream>
#include <string>

GameContainer:: GameContainer():
game_finished(false){}

bool GameContainer:: contains(const std::string& key) {
    return this->map.contains(key);
}

TaTeTi* GameContainer:: create_new_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        return this->map.add_new_game(new TaTeTi(key));
    }
    return NULL;
}

std::string GameContainer::get_all_values(){
    std::unique_lock<std::mutex> lk(this->m);
    return this->map.get_all_values();
}

TaTeTi* GameContainer::get_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    return this->map.get_game(key);
}

GameContainer:: ~GameContainer(){}
