#include "client.h"

int main(int argc, char const *argv[]){
    Client client(argv);
    
    client.communicate_with_server();

    return 0;
}
