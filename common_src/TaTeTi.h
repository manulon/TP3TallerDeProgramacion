#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

#include <string>

class TaTeTi {

private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    std::string name;
    
    void game_finished_with_a_winner(const bool& status);
    bool game_tied();
    bool check_rows();
    bool check_columns();
    bool check_diagonals();

public:
    TaTeTi();
    TaTeTi(const std::string& name);
    void printBoard();
    std::string get_board();
    void setNewPosition
    (const char& character,const int& column,const int& row);
    void set_name(const std::string& name);
    std::string get_name();
    void checkGameStatus();
    ~TaTeTi();
};

#endif
