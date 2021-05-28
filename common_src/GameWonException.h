#ifndef GAME_WON_EXCEPTION_H
#define GAME_WON_EXCEPTION_H

#include <exception>
#include "GameFinishedException.h"

class GameWonException : public GameFinishedException {
    virtual const char* what() override {
        return "\nFelicitaciones! Ganaste! \n";
    }
};

#endif
