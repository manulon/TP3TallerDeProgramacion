#include "ThreadAcceptor.h"
#include "../common_src/AcceptorClosedException.h"
#include "../common_src/SocketException.h"


ThreadAcceptor:: ThreadAcceptor
(GameContainer* games, const char* servicename):
keep_running(true), games(games), servicename(servicename) {}

void ThreadAcceptor:: run() {
    try{
        this->socket.bind_and_listen(NULL,this->servicename);
    }catch(SocketException& error){
        keep_running = false;
    }

    while (keep_running){
        Socket* peer = new Socket();
        try {
            if (this->socket.socket_accept(peer) < 0) {
                delete peer;
            }
            clients.push_back(new ThreadClient(peer,this->games));
            clients.back()->start();
        }catch(std::exception& error){
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

void ThreadAcceptor:: close_socket(){
    this->socket.socket_close();
}

ThreadAcceptor:: ~ThreadAcceptor(){}
