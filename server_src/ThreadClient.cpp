#include "ThreadClient.h"
#include <utility>

ThreadClient:: ThreadClient(Socket* peer, GameContainer* games):
peer(peer),games(games) {}

void ThreadClient:: run() {
    Server_Protocol sp(this->games);
    sp.init(std::move(*this->peer));
    sp.start_communication_protocol();

    int bytes_received(1);

    while (bytes_received > 0){
        bytes_received = sp.select_execution_mode();
    }
    shutdown(peer->get_fd(), SHUT_WR);
    dead = true;
}

void ThreadClient:: stop() {
    delete this->peer;
}

/*
bool ThreadClient:: is_dead() {
    return this->dead;
}*/

ThreadClient:: ~ThreadClient(){
    //this->join();
}
