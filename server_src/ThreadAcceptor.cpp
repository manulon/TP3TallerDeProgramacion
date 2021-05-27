#include "ThreadAcceptor.h"

ThreadAcceptor:: ThreadAcceptor(const Socket& s,GameContainer* games) {
    this->socket = s;
    this->games = games;
}

void ThreadAcceptor:: run() {
    while (keep_running) {
        Socket* peer = new Socket();
        if (this->socket.socket_accept(peer) < 0) {
            delete peer;
            break;
        }
        clients.push_back(new ThreadClient(peer,this->games));
        clients.back()->start();
        this->garbage_collector();
    }
}

void ThreadAcceptor:: garbage_collector() {
    std::list<ThreadClient*>::iterator it;
    it = this->clients.begin();
    while (it != this->clients.end()) {
        if ((*it)->is_dead()) {
            (*it)->stop();
            delete (*it);
            it = this->clients.erase(it);
        } else {
            ++it;
        }
    }
}

void ThreadAcceptor:: stop() {
    this->keep_running = false;
    shutdown(this->socket.get_fd(), SHUT_RDWR);
    close(this->socket.get_fd());
    std::list<ThreadClient*>::iterator it;
    for (it = this->clients.begin(); 
    it != this->clients.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
}

ThreadAcceptor:: ~ThreadAcceptor(){}
