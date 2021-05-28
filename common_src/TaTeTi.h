#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

#include <string>

class TaTeTi {

private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    std::string name;
    bool there_is_a_winner;
    
    void game_finished_with_a_winner(const bool& status,std::string& msg);
    bool game_tied();
    bool check_rows(const char& token);
    bool check_columns(const char& token);
    bool check_diagonals(const char& token);

public:
    TaTeTi();
    TaTeTi(const std::string& name);
    std::string get_board();
    void set_new_position
    (const char& character,const int& column,const int& row);
    void set_name(const std::string& name);
    std::string get_name();
    void check_game_status(const char& token,std::string& msg);
    ~TaTeTi();
};

#endif
