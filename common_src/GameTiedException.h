#ifndef GAME_TIED_EXCEPTION_H
#define GAME_TIED_EXCEPTION_H

#include <exception>
#include "GameFinishedException.h"

class GameTiedException : public GameFinishedException {
    virtual const char* what() override {
        return "\nLa partida ha terminado en empate\n";
    }
};

#endif
