#pragma once
#include "GameState.h"
#include <string>
class PauseState :
    public GameState
{
public:
    PauseState(SDLApplication*, const std::string&);
    void restartGame(const std::string&);
};

