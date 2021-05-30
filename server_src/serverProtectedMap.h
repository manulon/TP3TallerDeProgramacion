#ifndef SERVER_PROTECTED_MAP_H
#define SERVER_PROTECTED_MAP_H

#include "../common_src/TaTeTi.h"
#include <string>
#include <map>
#include <utility>

class ProtectedMap {
    std::map<std::string, TaTeTi*> internal;
    
public:
    ProtectedMap();
    ~ProtectedMap();

    bool contains(const std::string& key);
    void set_name(const std::string& key);
    void add_new_game(TaTeTi* game);
    std::string get_name(const std::string& key);
    std::string get_all_values();
    void make_play(const std::string& key,const char& token,
    const unsigned char& row, const unsigned char& column);
    std::string get_board(const std::string& game_name);
    std::string get_initial_board(const std::string& game_name);
    TaTeTi* get_game(const std::string& key);
    void check_game_status
    (const std::string& game_name,const char& token,std::string& msg);
    bool game_already_start(const std::string& key);
    void game_started(const std::string& key);
    void notify_winner(const std::string& key);
};

#endif
