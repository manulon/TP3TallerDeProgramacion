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
    
    //Delega la busqueda de una key en particular al mapa.
    bool contains(const std::string& key);

public:
    GameContainer();
    ~GameContainer();
    
    //Crea un nuevo juego, delega la inclusion de esta al
    //mapa y luego lo devuelve.
    //Pre: La key, que representa al nombre del juego, es valida.
    TaTeTi* create_new_game(const std::string& key);

    //Delega la obtencion de todos los valores del mapa.
    std::string get_all_values();

    //Devuelve un puntero al juego de nombre key.
    //Pre: El juego existe con el nombre recibido por parametro.
    TaTeTi* get_game(const std::string& key);
};

#endif
