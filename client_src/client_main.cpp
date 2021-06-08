#include "client.h"
#include "../common_src/SocketException.h"

int main(int argc, char const *argv[]){
    try{
        Client client(argv);
        client.communicate_with_server();
    }catch(SocketException& error){
        return 1;
    }
    return 0;
}
