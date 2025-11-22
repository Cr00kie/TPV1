#pragma once
#include "GameState.h"
class EndState :
    public GameState
{
public:
    EndState(SDLApplication*, bool victory);
};

