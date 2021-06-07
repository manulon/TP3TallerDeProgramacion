#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#define CREAR_KEYWORD "crear"
#define LISTAR_KEYWORD "listar"
#define UNIRSE_KEYWORD "unirse"
#define JUGAR_KEYWORD "jugar"
#define LISTAR_KEY "l"
#define JUGAR_KEY "p"
#define CREAR_KEY "n"
#define UNIRSE_KEY "j"
#define STANDARD_BOARD_SIZE 128


#include "../common_src/CommunicationProtocol.h"
#include <string>

class Client_Protocol{
    Socket socket;
    CommunicationProtocol comm;

private:
    //Selecciona el modo de ejecucion entre los cuatro validos.
    //Pre: Se ingresa un comando valido.
    void select_and_execute_mode(std::string& line);

    //Obtiene la primer palabra de la frase recibida por entrada
    //estandar, para asi poder ejecutar el modo buscado.
    std::string get_execution_mode(const std::string& line);

    //Ejecuta el modo jugar.
    //Pre: El formato de la linea recibida sera jugar X X,
    //con x pudiendo tomar los valores 1,2 y 3.
    void mode_play(std::string& line);

    //Ejecuta el modo crear.
    //Pre: El formato de la linea recibida sera crear *nombre*.
    void mode_create(std::string& line);

    //Ejecuta el modo listar.
    void mode_list();

    //Ejecuta el modo unirse.
    //Pre: El formato de la linea recibida sera unirse *nombre*.
    void mode_join(std::string& line);

    //Pone las dos posiciones recibidas por linea de comando
    //que refieren al movimiento en un byte para respetar el
    //protocolo de envio.
    unsigned char put_position_in_one_byte
    (unsigned char row, unsigned char column);

    //Obtiene la palabra clave del comando. Esta funcion se usa
    //en crear y unirse para obtener el nombre de la partida.
    void get_keyword
    (const std::string& keyword, std::string& line);

public:
    Client_Protocol();
    ~Client_Protocol();
    
    //Asigna el socket recibido por parametro como socket propio.
    void init(const Socket& socket);

    //Lee una linea de la 
    //entrada estandar y en funcion de ella delega la operacion partida
    //buscada.
    void start_communication_protocol();
};

#endif
