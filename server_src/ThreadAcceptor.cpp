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
            //this->garbage_collector();
        }catch(AcceptorClosedException& error){
            delete peer;
            keep_running = false;
        }
    }
    for (ThreadClient* client : clients) {
        client->join();
	}
}

/*void ThreadAcceptor:: garbage_collector() {
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
}*/
void ThreadAcceptor:: stop() {
    std::list<ThreadClient*>::iterator it;
    for (it = this->clients.begin(); 
    it != this->clients.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
}


void ThreadAcceptor:: stop_test(){
    keep_running = false;
}

ThreadAcceptor:: ~ThreadAcceptor(){}
