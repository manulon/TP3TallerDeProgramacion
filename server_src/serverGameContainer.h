#ifndef SERVER_GAME_CONTAINER_H
#define SERVER_GAME_CONTAINER_H

#include "serverProtectedMap.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

class GameContainer{
private:
    ProtectedMap map;
    std::mutex m;
    std::condition_variable cv;
    std::atomic<bool> game_finished; 

    bool contains(const std::string& key);

public:
    GameContainer();
    ~GameContainer();
    
    void create_new_game(const std::string& key);
    std::string get_game_name(const std::string& key);
    std::string get_all_values();
    void make_play(const char& token,const unsigned char& row,
        const unsigned char& column, const std::string& game_name);
    std::string get_board(const std::string& game_name);
    void check_game_status(const std::string& game_name,const char& token);
    std::string get_initial_board(const std::string& game_name);
    void finish_game();
};

#endif
