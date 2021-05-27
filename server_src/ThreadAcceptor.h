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
#include "serverProtocol.h"

class ThreadAcceptor: public Thread {
    Socket socket;
    std::list<ThreadClient*> clients;
    std::atomic<bool> keep_running{true};
    Server_Protocol sp;

    public:
    ThreadAcceptor(const Socket& socket, const Server_Protocol& sp);
    virtual void run() override;
    void stop();
    void garbage_collector();
    virtual ~ThreadAcceptor() override;
};

#endif