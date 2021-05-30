#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#define LISTAR_KEY "l"
#define JUGAR_KEY "p"
#define CREAR_KEY "n"
#define UNIRSE_KEY "j"
#define HOST_TOKEN 79
#define GUEST_TOKEN 88

#include "../common_src/CommunicationProtocol.h"
#include "../common_src/TaTeTi.h"
#include "serverGameContainer.h"
#include <atomic>
#include <string>

class Server_Protocol{
private:
    char token;
    std::string final_game_msg;
    Socket socket;
    CommunicationProtocol comm;
    TaTeTi* game;
    GameContainer* gc;

    int receive_size();
    int receive_message(const int& size);
    void makePlay(const char* message, const std::string& game_name);
    int get_execution_mode(char* mode);
    void receive_play_command();
    void send_board(const std::string& game_name);
    void check_game_status
    (const std::string& game_name,std::string& msg);
    void receive_create_command();
    void receive_list_command();
    void receive_join_command();
    void set_token(const char& token);

public:
    explicit Server_Protocol(GameContainer* games);
    void init(const Socket& socket);
    void start_communication_protocol();
    void select_execution_mode();
    ~Server_Protocol();
};

#endif
