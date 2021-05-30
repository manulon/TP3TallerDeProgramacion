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
        this->map.set_name(key);
    }
}

std::string GameContainer::get_all_values(){
    return this->map.get_all_values();
}

void GameContainer:: make_play
(const char& token,const unsigned char& row, 
const unsigned char& column, const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(game_name)){
        this->map.make_play(game_name,token,row,column);
        this->map.game_started(game_name);
        this->cv.notify_all();
    }
}

std::string GameContainer::get_board(const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (!this->game_finished){
        this->cv.wait(lk);
        if (contains(game_name))
            return this->map.get_board(game_name);
    }else{
        return this->map.get_board(game_name);
    }
    return 0;
}

std::string GameContainer:: get_initial_board(const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(game_name)){
            return this->map.get_board(game_name);
    }
    return 0;
}

void GameContainer::check_game_status
(const std::string& game_name,const char& token,std::string& msg){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(game_name)){
        this->map.check_game_status(game_name,token,msg);
    }
}

void GameContainer:: notify_winner(){
    std::unique_lock<std::mutex> lk(this->m);
    this->cv.notify_all();
}

bool GameContainer:: game_already_start(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(key)){
        return this->map.game_already_start(key);
    }
    return false;    
}

GameContainer:: ~GameContainer(){}
