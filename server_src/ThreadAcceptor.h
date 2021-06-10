#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include "Thread.h"
#include "../common_src/Socket.h"
#include "ThreadClient.h"
#include "serverGameContainer.h"

class ThreadAcceptor: public Thread {
    Socket socket;
    std::list<ThreadClient*> clients;
    std::atomic<bool> keep_running;
    GameContainer* games;
    const char* servicename;

    public:
    ThreadAcceptor(GameContainer* games, const char* servicename);
    virtual ~ThreadAcceptor() override;
    
    //Realiza el run del Thread Acceptor. Una vez que la operacion
    //principal del run termine, espera a que joineen todos los hilos
    //clientes que fueron lanzados.
    virtual void run() override;
    
    //Hace stop a todos los clientes.
    void stop_clients();
    
    //Deja de correr el hilo.
    void stop();

    void close_socket();

    void garbage_collector();
};

#endif
