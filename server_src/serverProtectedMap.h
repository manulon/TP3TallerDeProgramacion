#ifndef SERVER_PROTECTED_MAP_H
#define SERVER_PROTECTED_MAP_H

#include "TaTeTi.h"
#include <string>
#include <map>
#include <utility>

class ProtectedMap {
    std::map<std::string, TaTeTi*> internal;
    
public:
    ProtectedMap();
    ~ProtectedMap();

    //Devuelve un booleano que representa si el juego esta
    //presente en el mapa o no.
    bool contains(const std::string& key);

    //Delega el seteo de nombre del juego.
    void set_name(const std::string& key);

    //Agrega un nuevo juego al mapa y luego lo devuelve.
    TaTeTi* add_new_game(TaTeTi* game);

    //Devuelve el nombre del juego.
    std::string get_name(const std::string& key);

    //Devuelve todos los nombres de las partidas con el formato
    //requerido para que estas puedan ser mostradas con el comando
    //listar.
    std::string get_all_values();

    //Devuelve el puntero al juego de nombre key.
    TaTeTi* get_game(const std::string& key);
};

#endif
