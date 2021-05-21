#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common_src/CommunicationProtocol.h"

class Server_Protocol{
    Socket socket;
    CommunicationProtocol comm;

public:
    Server_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Server_Protocol();
};

#endif
