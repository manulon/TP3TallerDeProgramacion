#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"
#include "server.h"

#include <iostream>

int main(int argc, char const *argv[]){
    Server server(argv);

    if (!server.start_connection()){
        return 1;
    }

    server.start();

    std::string input("");
    while (input != "q") {
        std::cin >> input;
    }

    return 0;
}