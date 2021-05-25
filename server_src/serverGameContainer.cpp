#include "serverGameContainer.h"

GameContainer:: GameContainer(){}

bool GameContainer:: contains(const std::string& key) {
    return this->map.contains(key);
}

void GameContainer:: create_new_game(const std::string& key){
    //std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        this->map.set_name(key);
    }
}

std::string GameContainer::get_game_name(const std::string& key){
    return this->map.get_name(key);
}

GameContainer:: ~GameContainer(){}
