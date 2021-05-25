#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#define CREAR_KEYWORD "crear"
#define LISTAR_KEYWORD "listar"
#define UNIRSE_KEYWORD "unirse"
#define JUGAR_KEYWORD "jugar"
#define LISTAR_KEY "l"
#define JUGAR_KEY "p"
#define CREAR_KEY "n"

#include "../common_src/CommunicationProtocol.h"
#include <string>

class Client_Protocol{
    Socket socket;
    CommunicationProtocol comm;

private:
    void select_execution_mode(std::string& line);
    std::string get_execution_mode(const std::string& line);
    void mode_play(std::string& line);
    void mode_create(std::string& line);
    void mode_list();

public:
    Client_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Client_Protocol();
};

#endif
