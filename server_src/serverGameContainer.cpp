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

void GameContainer:: make_play
(const char& token,const unsigned char& row, 
const unsigned char& column, const std::string& game_name){
    if (contains(game_name)){
        this->map.make_play(game_name,token,row,column);
        this->map.game_started(game_name);
    }
}

std::string GameContainer::get_board(const std::string& game_name){
    std::unique_lock<std::mutex> lk(this->m);
    if (!this->game_finished){
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
            return this->map.get_initial_board(game_name);
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

void GameContainer:: notify_winner(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(key)){
        this->map.notify_winner(key);
    }   
}

bool GameContainer:: game_already_start(const std::string& key){
    std::unique_lock<std::mutex> lk(this->m);
    if (contains(key)){
        return this->map.game_already_start(key);
    }
    return false;    
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
