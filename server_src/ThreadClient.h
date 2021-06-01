#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include "Thread.h"
#include "../common_src/Socket.h"
#include "serverGameContainer.h"
#include "serverProtocol.h"

class ThreadClient: public Thread {
    Socket* peer;
    std::mutex mtx;
    std::atomic<bool> keep_running;
    GameContainer* games;

    public:
    ThreadClient(Socket* peer, GameContainer* games);
    virtual ~ThreadClient() override;
    
    //Hace la operacion del run del hilo. Una vez que la
    //operacion principal termina, le hace un shutdown al 
    //socket asociado.
    virtual void run() override;
    
    //Elimina el socket asociado.
    void stop();
};

#endif
