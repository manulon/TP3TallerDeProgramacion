#include "ThreadClient.h"
#include <utility>

ThreadClient:: ThreadClient(Socket* peer, GameContainer* games):
peer(peer),keep_running(true),games(games),is_still_running(true) {}

void ThreadClient:: run() {
    Server_Protocol sp(this->games,this->peer);
    
    int bytes_received(1);

    while (bytes_received > 0){
        bytes_received = sp.select_execution_mode();
    }
    is_still_running=false;
    peer->socket_shutdown();
}

bool ThreadClient:: is_running(){
    return is_still_running;
}

void ThreadClient:: stop() {
    delete this->peer;
}

ThreadClient:: ~ThreadClient(){}
