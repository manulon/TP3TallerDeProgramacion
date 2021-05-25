#ifndef SERVER_GAME_CONTAINER_H
#define SERVER_GAME_CONTAINER_H

#include "serverProtectedMap.h"

class GameContainer{
private:
    ProtectedMap map;
    bool contains(const std::string& key);

public:
    GameContainer();
    ~GameContainer();
    
    void create_new_game(const std::string& key);
    std::string get_game_name(const std::string& key);
};

#endif
