#ifndef GAME_LOSS_EXCEPTION_H
#define GAME_LOSS_EXCEPTION_H

#include <exception>
#include "GameFinishedException.h"

class GameLossException : public GameFinishedException {
    virtual const char* what() override {
        return "\nHas perdido. Segui intentando!\n \n";
    }
};

#endif
