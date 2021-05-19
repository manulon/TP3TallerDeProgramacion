#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

class TaTeTi {

private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    void gameFinished(bool status);
    bool check_rows();
    bool check_columns();
    bool check_diagonals();

public:
    TaTeTi();
    void printBoard();
    void setNewPosition(char character, int row, int column);
    void checkGameStatus();
    ~TaTeTi();
};

#endif
