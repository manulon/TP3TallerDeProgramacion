#include "ThreadClient.h"

ThreadClient:: ThreadClient(Socket* peer, const Server_Protocol& sp) {
    this->peer = peer;
    this->sp = sp;
}

void ThreadClient:: run() {
    this->sp.init(std::move(*this->peer));
    this->sp.start_communication_protocol();

    while (keep_running){
        try {
            this->sp.select_execution_mode();
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
