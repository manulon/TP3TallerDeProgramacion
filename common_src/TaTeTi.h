#ifndef TA_TE_TI_H
#define TA_TE_TI_H

#define ROW_LENGTH 3
#define COLUMN_LENGTH 3

#include <string>
#include <mutex>
#include <condition_variable>

class TaTeTi {
private:
    char board[ROW_LENGTH][COLUMN_LENGTH];
    std::string name;
    bool there_is_a_winner;
    bool a_play_was_made;
    std::mutex m;
    std::condition_variable cv;

    void initialize_board();
    void game_finished_with_a_winner(const bool& status,std::string& msg);
    bool game_tied();
    bool check_rows(const char& token);
    bool check_columns(const char& token);
    bool check_diagonals(const char& token);

public:
    TaTeTi();
    explicit TaTeTi(const std::string& name);
    std::string get_board();
    std::string get_initial_board();
    void set_new_position
    (const char& character,const int& column,const int& row);
    void set_name(const std::string& name);
    std::string get_name();
    void check_game_status(const char& token,std::string& msg);
    bool game_already_start();
    void opponent_turn();
    void notify_winner();
    TaTeTi& operator=(const TaTeTi &t);
    ~TaTeTi();
};

#endif
