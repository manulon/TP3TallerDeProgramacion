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


    public:
    ThreadAcceptor(const Socket& socket,GameContainer* games);
    virtual void run() override;
    void stop_clients();
    void stop();
    virtual ~ThreadAcceptor() override;
};

#endif
