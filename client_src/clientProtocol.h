#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/CommunicationProtocol.h"
#include <string>

class Client_Protocol{
    Socket socket;
    CommunicationProtocol comm;

private:
    void select_execution_mode(std::string& line);
    std::string get_execution_mode(const std::string& line);
    void mode_play(std::string& line);
    void mode_create(const std::string& line);

public:
    Client_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Client_Protocol();
};

#endif
