#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#define LISTAR_KEY "l"
#define JUGAR_KEY "p"
#define CREAR_KEY "n"
#define HOST_TOKEN 79
#define GUEST_TOKEN 88

#include "../common_src/CommunicationProtocol.h"
#include "../common_src/TaTeTi.h"
#include "serverGameContainer.h"

class Server_Protocol{
private:
    char token;
    Socket socket;
    CommunicationProtocol comm;
    TaTeTi game;
    GameContainer gc;

    int receive_size();
    int receive_message(const int& size);
    void makePlay(const char* message);
    int get_execution_mode(char* mode);
    void select_execution_mode();
    void receive_play();
    void send_board();
    void send_board_with_message();
    void check_game_status();
    void receive_game_name();
    void receive_list_command();
    void set_token(const char& token);

public:
    Server_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Server_Protocol();
};

#endif
