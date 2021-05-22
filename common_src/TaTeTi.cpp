#include "TaTeTi.h"
#include "GameWonException.h"
#include "GameTiedException.h"
#include <iostream>

TaTeTi:: TaTeTi(){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            /*Empty space*/
            this->board[i][j] = 32;
        }
    }
}

TaTeTi:: TaTeTi(std::string name){
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            /*Empty space*/
            this->board[i][j] = 32;
        }
    }
    this->name = name;
}

void TaTeTi:: printBoard(){
    std::cout <<"    1 . 2 . 3 ."<<std::endl;
    std::cout <<"  +---+---+---+"<<std::endl;
    std::cout <<"1 | "<< this->board[0][0] <<" | ";
    std::cout << this->board[0][1] <<" | ";
    std::cout << this->board[0][2] <<" |"<<std::endl;
    std::cout <<"  +---+---+---+"<<std::endl;
    std::cout <<"2 | "<< this->board[1][0] <<" | ";
    std::cout << this->board[1][1] <<" | ";
    std::cout << this->board[1][2] <<" |"<<std::endl;
    std::cout <<"  +---+---+---+"<<std::endl;
    std::cout <<"3 | "<< this->board[2][0] <<" | ";
    std::cout << this->board[2][1] <<" | ";
    std::cout << this->board[2][2] <<" |"<<std::endl;
    std::cout <<"  +---+---+---+"<<std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void TaTeTi:: setName(std::string name){
    this->name = name;
}

void TaTeTi:: setNewPosition(char character, int column, int row){
    this->board[row-1][column-1] = character;
}

void TaTeTi:: checkGameStatus(){
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

void TaTeTi:: game_finished_with_a_winner(bool status){   
    if( status == true ){
        std::cout << "Felicitaciones, eres el ganador !" << std::endl;
        throw GameWonException();
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
