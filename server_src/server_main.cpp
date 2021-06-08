#include "TaTeTi.h"
#include "server.h"

#include <iostream>

int main(int argc, char const *argv[]){
    Server server(argv);
    
    server.start();
    
    std::string input("");
    while (input != "q") {
        std::cin >> input;
    }

    server.stop_accepting();

    return 0;
}
