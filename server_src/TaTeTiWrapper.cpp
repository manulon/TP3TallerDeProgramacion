#include "TaTeTiWrapper.h"
#include <iostream>
#include <sstream>

TaTeTiWrapper:: TaTeTiWrapper():
game(nullptr),actual_token(HOST_TOKEN),guest_joined(false){}

std::string TaTeTiWrapper::get_board(){
    std::unique_lock<std::mutex> lk(this->m);
    return this->game->get_board();
}

void TaTeTiWrapper:: set_name
(const std::string& name){
    std::unique_lock<std::mutex> lk(this->m);
    this->game->set_name(name);
}

std::string TaTeTiWrapper::get_name(){
    std::unique_lock<std::mutex> lk(this->m);
    return this->game->get_name();
}

std::string TaTeTiWrapper::set_new_position(char character,int column,int row){
    std::unique_lock<std::mutex> lk(this->m);
    while (!guest_joined){this->cv.wait(lk);}
    this->game->set_new_position(character,column,row);
    change_turn();
    while (!its_player_turn(character)){
        this->cv.wait(lk);
    }
    return this->game->get_board(); 
}

bool TaTeTiWrapper:: its_player_turn(char token){
    if (actual_token == token)
        return true;
    return false;
}

void TaTeTiWrapper:: change_turn(){
    if (actual_token == HOST_TOKEN){
        actual_token = GUEST_TOKEN;
    }else{
        actual_token = HOST_TOKEN;
    }
    this->cv.notify_all();
}

void TaTeTiWrapper:: check_game_status(char token,std::string& msg){
    std::unique_lock<std::mutex> lk(this->m);
    this->game->check_game_status(token,msg);
}

void TaTeTiWrapper:: notify_winner(){
    std::unique_lock<std::mutex> lk(this->m);
    change_turn();
}

void TaTeTiWrapper:: guest_join_game(){
    std::unique_lock<std::mutex> lk(this->m);
    this->guest_joined = true;
    this->cv.notify_all();
    this->cv.wait(lk);
}

void TaTeTiWrapper:: wrap(TaTeTi* game){
    std::unique_lock<std::mutex> lk(this->m);
    this->game = game;
}

void TaTeTiWrapper:: unwrap(){
    delete this->game;
}

TaTeTiWrapper:: ~TaTeTiWrapper(){}
