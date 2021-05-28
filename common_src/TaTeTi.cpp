#include "TaTeTi.h"
#include "GameLossException.h"
#include "GameTiedException.h"
#include <iostream>

TaTeTi:: TaTeTi(){
    /*funcion*/
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            /*Empty space*/
            this->board[i][j] = 32;
        }
    }
}

TaTeTi:: TaTeTi(const std::string& name){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            /*Empty space*/
            this->board[i][j] = 32;
        }
    }
    this->name = name;
}

std::string TaTeTi::get_board(){
    std::string board("");

    board += ("    1 . 2 . 3 .\n");
    board += ("  +---+---+---+\n");
    board += ("1 | ");
    board += this->board[0][0];
    board += (" | ");
    board += this->board[0][1];
    board += (" | ");
    board += this->board[0][2];
    board += (" |\n  +---+---+---+\n");
    board += ("2 | ");
    board += this->board[1][0];
    board += (" | ");
    board += this->board[1][1];
    board += (" | ");
    board += this->board[1][2];
    board += (" |\n");
    board += ("  +---+---+---+\n");
    board += ("3 | ");
    board += this->board[2][0];
    board += (" | ");
    board += this->board[2][1];
    board += (" | ");
    board += this->board[2][2];
    board += (" |\n");
    board += ("  +---+---+---+");

    return board;
}

void TaTeTi:: set_name
(const std::string& name){
    this->name = name;
}

std::string TaTeTi::get_name(){
    return this->name;
}

void TaTeTi:: set_new_position
(const char& character,const int& column,const int& row){
    this->board[row-1][column-1] = character;
}

void TaTeTi:: check_game_status(const char& token){
    bool is_there_a_winner = false;
       
    is_there_a_winner = check_rows();

    is_there_a_winner = is_there_a_winner || check_columns();

    is_there_a_winner = is_there_a_winner || check_diagonals();

    game_finished_with_a_winner(is_there_a_winner);

    if ( game_tied() ){
        std::cout << "Empate !" << std::endl;
        throw GameTiedException();
    }
}

bool TaTeTi:: game_tied(){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            if ( this->board[i][j] == 32 )
                return false;
        }
    }
    return true;
}

void TaTeTi:: game_finished_with_a_winner(const bool& status){
    if( status == true ){
        throw GameLossException();
    }
}

bool TaTeTi:: check_rows(){
    int row = 0;

    while (row < 3) {
        if ( (this->board[row][0] == this->board[row][1])
          && (this->board[row][1] == this->board[row][2])
          && (this->board[row][0] != 32 ) ){
            return true;}
        row++;
    }
    return false;
}

bool TaTeTi:: check_columns(){
    int column = 0;

    while (column < 3) {
        if ( (this->board[0][column] == this->board[1][column])
          && (this->board[1][column] == this->board[2][column])
          && (this->board[0][column] != 32 ) )
            return true;
        column++;
    }
    return false;
}

bool TaTeTi:: check_diagonals(){
    if ( (this->board[0][0] == this->board[1][1])
      && (this->board[1][1] == this->board[2][2])
      && (this->board[0][0] != 32 ) )
            return true;

    if ( (this->board[0][2] == this->board[1][1])
      && (this->board[1][1] == this->board[2][0])
      && (this->board[0][2] != 32 ) )
            return true;
    
    return false;
}

TaTeTi:: ~TaTeTi(){}
