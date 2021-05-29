#include "ThreadClient.h"
#include <utility>

ThreadClient:: ThreadClient(Socket* peer, GameContainer* games) {
    this->peer = peer;
    this->games = games;
}

void ThreadClient:: run() {
    Server_Protocol sp(this->games);
    sp.init(std::move(*this->peer));
    sp.start_communication_protocol();

    while (keep_running){
        try {
            sp.select_execution_mode();
        } catch (...) {
            if (!keep_running) break;
        } 
    }
    shutdown(peer->get_fd(), SHUT_WR);
    dead = true;
}

void ThreadClient:: stop() {
    keep_running = false;
    delete this->peer;
}

bool ThreadClient:: is_dead() {
    return this->dead;
}

ThreadClient:: ~ThreadClient(){
    this->join();
}
