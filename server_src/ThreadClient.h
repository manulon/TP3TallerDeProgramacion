#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include "Thread.h"
#include "../common_src/Socket.h"
#include "serverProtocol.h"

class ThreadClient: public Thread {
    Socket* peer;
    std::mutex mtx;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};
    Server_Protocol sp;

    public:
    ThreadClient(Socket* peer, const Server_Protocol& sp);
    virtual void run() override;
    void stop();
    bool is_dead();
    virtual ~ThreadClient() override;
};

#endif