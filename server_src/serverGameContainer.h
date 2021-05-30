#ifndef SERVER_GAME_CONTAINER_H
#define SERVER_GAME_CONTAINER_H

#include "serverProtectedMap.h"
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>

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
    std::string get_all_values();
    std::string get_board(const std::string& game_name);
    TaTeTi* get_game(const std::string& key);
    void add_new_game(TaTeTi* game);
};

#endif
