#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

#include <string>

class TaTeTi {

private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    std::string name;
    
    void game_finished_with_a_winner(bool status);
    bool game_tied();
    bool check_rows();
    bool check_columns();
    bool check_diagonals();

public:
    TaTeTi();
    TaTeTi(std::string name);
    void printBoard();
    void setNewPosition(char character, int column, int row);
    void setName(std::string name);
    void checkGameStatus();
    ~TaTeTi();
};

#endif
