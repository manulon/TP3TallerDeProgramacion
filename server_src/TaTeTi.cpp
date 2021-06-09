#include "TaTeTi.h"
#include <iostream>
#include <sstream>


TaTeTi:: TaTeTi(const std::string& key):
name(key),there_is_a_winner(false),first_get_board(true){
    initialize_board();
}

void TaTeTi:: initialize_board(){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            this->board[i][j] = ' ';
        }
    }
}

std::string TaTeTi::get_board(){      
    std::ostringstream board;

    board << "    1 . 2 . 3 .\n  +---+---+---+\n1 | ";   
    board << this->board[0][0]<< " | "<< this->board[0][1]<< " | ";
    board << this->board[0][2];
    board << " |\n  +---+---+---+\n2 | "<< this->board[1][0]<< " | ";
    board << this->board[1][1]<< " | "<< this->board[1][2]<< " |\n";
    board << "  +---+---+---+\n3 | "<< this->board[2][0]<< " | ";
    board << this->board[2][1]<< " | "<< this->board[2][2]<< " |\n";
    board << "  +---+---+---+\n";

    if ( there_is_a_winner )
        board << "Felicitaciones! Ganaste!\n";

    return board.str();
}

void TaTeTi:: set_name
(const std::string& name){
    this->name = name;
}

std::string TaTeTi::get_name(){
    return this->name;
}

void TaTeTi:: set_new_position(char character,int column,int row){
    this->board[row-1][column-1] = character;
}

void TaTeTi:: check_game_status(char token,std::string& msg){
    bool is_a_loser = false;
       
    is_a_loser = check_rows(token);

    is_a_loser = is_a_loser || check_columns(token);

    is_a_loser = is_a_loser || check_diagonals(token);

    game_finished_with_a_winner(is_a_loser,msg);

    if ( game_tied() && !there_is_a_winner )
        msg = "La partida ha terminado en empate\n";
}

bool TaTeTi:: game_tied(){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            if ( this->board[i][j] == ' ' )
                return false;
        }
    }
    return true;
}

void TaTeTi:: game_finished_with_a_winner(bool status, std::string& msg){
    if ( status == true ){
        msg = "Has perdido. Segui intentando!\n";
        this->there_is_a_winner = true;
    }
}

bool TaTeTi:: check_rows(char token){
    int row = 0;

    while (row < 3) {
        if ( (this->board[row][0] == this->board[row][1])
          && (this->board[row][1] == this->board[row][2])
          && (this->board[row][0] != ' ' )
          && (this->board[row][0] != token)){
            return true;
        }
        row++;
    }
    return false;
}

bool TaTeTi:: check_columns(char token){
    int column = 0;

    while (column < 3) {
        if ( (this->board[0][column] == this->board[1][column])
          && (this->board[1][column] == this->board[2][column])
          && (this->board[0][column] != ' ' )
          && (this->board[0][column] != token) )
            return true;
        column++;
    }
    return false;
}

bool TaTeTi:: check_diagonals(char token){
    if ((this->board[0][0] == this->board[1][1])
      && (this->board[1][1] == this->board[2][2])
      && (this->board[0][0] != ' ' ) 
      && (this->board[1][1] != token))
            return true;

    if ((this->board[0][2] == this->board[1][1])
      && (this->board[1][1] == this->board[2][0])
      && (this->board[0][2] != ' ' ) 
      && (this->board[1][1] != token))
            return true;
    
    return false;
}

void TaTeTi:: notify_winner(){}

TaTeTi:: ~TaTeTi(){}
