#ifndef GAME_FINISHED_EXCEPTION_H
#define GAME_FINISHED_EXCEPTION_H

#include <exception>

class GameFinishedException : public std::exception {
    public:
        virtual const char* what() = 0;
};

#endif