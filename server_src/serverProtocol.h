#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common_src/CommunicationProtocol.h"
#include "../common_src/TaTeTi.h"

class Server_Protocol{
private:
    Socket socket;
    CommunicationProtocol comm;
    TaTeTi game;
    int receive_size();
    int receive_message(int size);
    void makePlay(const char* message);
public:
    Server_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Server_Protocol();
};

#endif
