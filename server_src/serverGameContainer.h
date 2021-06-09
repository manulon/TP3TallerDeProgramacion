#ifndef SERVER_GAME_CONTAINER_H
#define SERVER_GAME_CONTAINER_H

#include "TaTeTiWrapper.h"
#include <map>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>

class GameContainer{
private:
    std::map<std::string, TaTeTiWrapper*> internal;
    std::mutex m;
    std::condition_variable cv;
    std::atomic<bool> game_finished;
    
    //Busca una key en particular.
    bool contains(const std::string& key);

public:
    GameContainer();
    ~GameContainer();
    
    //Crea un nuevo juego, lo incluye al
    //mapa y luego lo devuelve.
    //Pre: La key, que representa al nombre del juego, es valida.
    TaTeTiWrapper* create_new_game(const std::string& key);

    //Obtiene todos los valores del mapa.
    std::string get_all_values();

    //Devuelve un puntero al juego de nombre key.
    //Pre: El juego existe con el nombre recibido por parametro.
    TaTeTiWrapper* get_game(const std::string& key);
};

#endif
