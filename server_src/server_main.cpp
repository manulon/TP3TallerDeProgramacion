#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"
#include "server.h"

#include <iostream>

int main(int argc, char const *argv[]){
    Server server(argv);

    server.communicate_with_client();

    return 0;
}