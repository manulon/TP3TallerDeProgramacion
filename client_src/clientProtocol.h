#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#define CREAR_KEYWORD "crear"
#define LISTAR_KEYWORD "listar"
#define UNIRSE_KEYWORD "unirse"
#define JUGAR_KEYWORD "jugar"
#define LISTAR_KEY "l"
#define JUGAR_KEY "p"
#define CREAR_KEY "n"
#define HOST_TOKEN "X"
#define GUEST_TOKEN "O"

#include "../common_src/CommunicationProtocol.h"
#include <string>

class Client_Protocol{
    char token;
    Socket socket;
    CommunicationProtocol comm;

private:
    void select_execution_mode(std::string& line);
    std::string get_execution_mode(const std::string& line);
    void mode_play(std::string& line);
    void mode_create(std::string& line);
    void mode_list();
    void mode_join();
    unsigned char put_position_in_one_byte
    (unsigned char row, unsigned char column);

public:
    Client_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Client_Protocol();
};

#endif
