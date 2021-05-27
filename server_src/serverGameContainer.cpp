#include "serverGameContainer.h"
#include <iostream>

GameContainer:: GameContainer(){}

bool GameContainer:: contains(const std::string& key) {
    return this->map.contains(key);
}

void GameContainer:: create_new_game(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        this->map.set_name(key);
    }
}

std::string GameContainer::get_game_name(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (!contains(key)) {
        return this->map.get_name(key);
    }
    return 0;
}

std::string GameContainer::get_all_values(){
    return this->map.get_all_values();
}

void GameContainer:: make_play
(const char& token,const unsigned char& row, 
const unsigned char& column, const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(game_name)){
        this->cv.notify_all();
        this->map.make_play(game_name,token,row,column);      
    }
}

std::string GameContainer::get_board(const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    this->cv.wait(lk);
    if (contains(game_name)){
        return this->map.get_board(game_name);
    }
    return 0;
}

void GameContainer::check_game_status(const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(game_name)){
        this->map.check_game_status(game_name);
    }
}

GameContainer:: ~GameContainer(){}
