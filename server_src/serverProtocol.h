#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#define LISTAR_KEY 'l'
#define JUGAR_KEY 'p'
#define CREAR_KEY 'n'
#define UNIRSE_KEY 'j'
#define HOST_TOKEN 'O'
#define GUEST_TOKEN 'X'

#include "../common_src/CommunicationProtocol.h"
#include "TaTeTiWrapper.h"
#include "serverGameContainer.h"
#include <atomic>
#include <string>

class Server_Protocol{
private:
    char token;
    std::string final_game_msg;
    Socket* socket;
    CommunicationProtocol comm;
    TaTeTiWrapper* game_wrapper;
    GameContainer* gc;    
    
    //Delega al juego la realizacion un movimiento.
    //Pre: El nombre de juego recibido por parametro es valido.
    void makePlay(char message, const std::string& game_name);
    
    //Recibe un byte que representa el identificador del tipo de jugada
    //a realizar.
    //Pre: El identificador recibido es valido.
    int get_execution_mode(char& mode);
    
    //Recibe el mensaje del cliente con la jugada a realizar y ejecuta
    //las funciones necesarias para realizar las jugadas.
    void receive_play_command();
        
    //Recibe el mensaje del cliente con la creacion de la partida y 
    //ejecuta las funciones necesarias para llevarla a cabo.
    void receive_create_command();
    
    //Recibe el mensaje del cliente que refiere al listado de partidas y 
    //ejecuta las funciones necesarias para llevarla a cabo.
    void receive_list_command();
    
    //Recibe el mensaje del cliente con el nombre de la partida a 
    //unirse y ejecuta las funciones necesarias para llevarla a cabo.
    void receive_join_command();
    
    //Setea el token al jugador.
    void set_token(const char& token);

    //Decodifica la columna y la fila respectivamente para ejecutar 
    //la jugada.
    int decode_column(char message);
    int decode_row(char message);

public:
    Server_Protocol(GameContainer* games,Socket* socket);
    ~Server_Protocol();
        
    //Recibe un byte que representa el identificador de comando a
    //realizar y lo realiza, si ya no recibe mas nada. Deja de esperar por
    //un identificador.
    int select_execution_mode();
};

#endif
