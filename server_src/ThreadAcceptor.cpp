#include "ThreadAcceptor.h"
#include "../common_src/AcceptorClosedException.h"

ThreadAcceptor:: ThreadAcceptor(const Socket& s,GameContainer* games):
keep_running(true) {
    this->socket = s;
    this->games = games;
}

void ThreadAcceptor:: run() {
    while (keep_running){
        Socket* peer = new Socket();
        try {
            if (this->socket.socket_accept(peer) < 0) {
                delete peer;
            }
            clients.push_back(new ThreadClient(peer,this->games));
            clients.back()->start();
        }catch(AcceptorClosedException& error){
            delete peer;
            keep_running = false;
        }
    }
    for (ThreadClient* client : clients) {
        client->join();
	}
}

void ThreadAcceptor:: stop_clients() {
    std::list<ThreadClient*>::iterator it;
    for (it = this->clients.begin(); 
    it != this->clients.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
}

void ThreadAcceptor:: stop(){
    keep_running = false;
}

ThreadAcceptor:: ~ThreadAcceptor(){}
