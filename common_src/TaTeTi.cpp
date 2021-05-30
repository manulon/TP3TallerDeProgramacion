#include "TaTeTi.h"
#include <iostream>

TaTeTi:: TaTeTi():
name(),there_is_a_winner(false),a_play_was_made(false){
    initialize_board();
}

TaTeTi:: TaTeTi(const std::string& name):
name(name),there_is_a_winner(false), a_play_was_made(false){
    initialize_board();
}

void TaTeTi:: initialize_board(){
    std::unique_lock<std::mutex> lk(this->m);
    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            /*Empty space*/
            this->board[i][j] = 32;
        }
    }
}

std::string TaTeTi::get_board(){
    std::unique_lock<std::mutex> lk(this->m);
    
    this->cv.wait(lk);

    std::string board("");

    board =  ("    1 . 2 . 3 .\n");
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
    board += ("  +---+---+---+\n");

    if ( there_is_a_winner )
        board += "Felicitaciones! Ganaste!\n";

    return board;
}

std::string TaTeTi::get_initial_board(){
    std::unique_lock<std::mutex> lk(this->m);
    std::string board("");
    
    board =  ("    1 . 2 . 3 .\n");
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
    board += ("  +---+---+---+\n");

    return board;
}

void TaTeTi:: set_name
(const std::string& name){
    std::unique_lock<std::mutex> lk(this->m);
    this->name = name;
}

std::string TaTeTi::get_name(){
    std::unique_lock<std::mutex> lk(this->m);
    return this->name;
}

void TaTeTi:: set_new_position
(const char& character,const int& column,const int& row){
    std::unique_lock<std::mutex> lk(this->m);
    this->board[row-1][column-1] = character;
}

void TaTeTi:: check_game_status(const char& token,std::string& msg){
    std::unique_lock<std::mutex> lk(this->m);
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
            if ( this->board[i][j] == 32 )
                return false;
        }
    }
    return true;
}

void TaTeTi:: game_finished_with_a_winner
(const bool& status, std::string& msg){
    if ( status == true ){
        msg = "Has perdido. Segui intentando!\n";
        this->there_is_a_winner = true;
    }
}

bool TaTeTi:: check_rows(const char& token){
    int row = 0;

    while (row < 3) {
        if ( (this->board[row][0] == this->board[row][1])
          && (this->board[row][1] == this->board[row][2])
          && (this->board[row][0] != 32 )
          && (this->board[row][0] != token)){
            return true;
        }
        row++;
    }
    return false;
}

bool TaTeTi:: check_columns(const char& token){
    int column = 0;

    while (column < 3) {
        if ( (this->board[0][column] == this->board[1][column])
          && (this->board[1][column] == this->board[2][column])
          && (this->board[0][column] != 32 )
          && (this->board[0][column] != token) )
            return true;
        column++;
    }
    return false;
}

bool TaTeTi:: check_diagonals(const char& token){
    if ((this->board[0][0] == this->board[1][1])
      && (this->board[1][1] == this->board[2][2])
      && (this->board[0][0] != 32 ) 
      && (this->board[1][1] != token))
            return true;

    if ((this->board[0][2] == this->board[1][1])
      && (this->board[1][1] == this->board[2][0])
      && (this->board[0][2] != 32 ) 
      && (this->board[1][1] != token))
            return true;
    
    return false;
}

bool TaTeTi:: game_already_start(){
    std::unique_lock<std::mutex> lk(this->m);
    return a_play_was_made;
}

void TaTeTi:: opponent_turn(){
    std::unique_lock<std::mutex> lk(this->m);
    this->cv.notify_all();
    this->a_play_was_made = true;
    
}

void TaTeTi:: notify_winner(){
    std::unique_lock<std::mutex> lk(this->m);
    this->cv.notify_all();
}

TaTeTi &TaTeTi::operator=(const TaTeTi &t){
    std::unique_lock<std::mutex> lk(this->m);
    this->name = t.name;
    this->there_is_a_winner = t.there_is_a_winner;
    this->a_play_was_made = t.a_play_was_made;

    for (int i=0 ; i<ROW_LENGTH; i++){
        for (int j=0 ; j<COLUMN_LENGTH ; j++){
            this->board[i][j] = t.board[i][j];
        }
    }
    return *this;
}

TaTeTi:: ~TaTeTi(){}
