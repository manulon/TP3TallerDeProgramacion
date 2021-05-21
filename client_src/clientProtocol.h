#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/CommunicationProtocol.h"

class Client_Protocol{
    Socket socket;
    CommunicationProtocol comm;

public:
    Client_Protocol();
    void init(const Socket& socket);
    void start_communication_protocol();
    ~Client_Protocol();
};

#endif
