#include "../common_src/TaTeTi.h"
#include "../common_src/GameFinishedException.h"
#include "server.h"

int main(int argc, char const *argv[]){
    TaTeTi tateti("Partida 1");
    /*bool keep_playing = true;

    while(keep_playing){
        try{
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(88,1,1);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(79,1,2);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(88,2,1);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(79,2,2);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(88,3,2);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(79,3,3);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(79,3,1);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(79,2,3);
            tateti.printBoard();
            tateti.checkGameStatus();
            tateti.setNewPosition(88,1,3);
            tateti.printBoard();
            tateti.checkGameStatus();
        } catch ( GameFinishedException &error ){
            keep_playing = false;
        }
    }*/

    Server server(argv);

    server.communicate_with_client();

    return 0;
}