#ifndef TA_TE_TI_WRAPPER_H
#define TA_TE_TI_WRAPPER_H

#include "TaTeTi.h"
#include <string>
#include <mutex>
#include <condition_variable>

class TaTeTiWrapper{
    TaTeTi* game;
    bool guest_joined;
    std::mutex m;
    std::condition_variable cv;

public: 
    TaTeTiWrapper();
    ~TaTeTiWrapper(); 

    //Devuelve el tablero en su estado actual.
    std::string get_board();
        
    //Realiza una nueva jugada y luego devuelve el tablero en su estado actual.
    std::string set_new_position(char character,int column,int row);
    
    //Setea el nombre del juego.
    void set_name(const std::string& name);
    
    //Devuelve el nombre del juego.
    std::string get_name();
    
    //Delega al tateti wrappeado el chequeo del estado actual del juego.
    void check_game_status(char token,std::string& msg);
    
    //Notifica que ha habido un ganador.
    void notify_winner();

    //Notifica que un segundo jugador a ingresado a la partida y esta esta lista
    //para comenzar.
    void guest_join_game();

    //Aqui se hace la asignacion de la partida a el wrapper
    void wrap(TaTeTi* game);
    
    //Se "desenvuelve" al juego que esta siendo envuelto por el wrapper.
    void unwrap();
};

#endif
