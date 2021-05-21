#ifndef SERVER_H
#define SERVER_H

#include "../common_src/Socket.h"
#include "../common_src/CommunicationProtocol.h"
//#include "clientProtocol.h"
#include <string>

class Server{
private:
    const char*  servicename;
    char* message_read;
    short int message_read_length;
    Socket socket;
    Socket peer;
    //Client_Protocol protocol;

    bool start_connection(Socket& socket,Socket& peer);

public:
    Server(char const* argv[]);
    ~Server();

    void communicate_with_client();
};

#endif
