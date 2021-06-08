#include "ThreadClient.h"
#include <utility>

ThreadClient:: ThreadClient(Socket* peer, GameContainer* games):
peer(peer),keep_running(true),games(games) {}

void ThreadClient:: run() {
    Server_Protocol sp(this->games,this->peer);
    
    int bytes_received(1);

    while (bytes_received > 0){
        bytes_received = sp.select_execution_mode();
    }
    peer->socket_shutdown();
}

void ThreadClient:: stop() {
    delete this->peer;
}

ThreadClient:: ~ThreadClient(){}
