#pragma once
#include "GameState.h"
#include <string>

class PlayState;

class PauseState :
    public GameState
{
    PlayState* m_pPlayState;
public:
    PauseState(SDLApplication*, PlayState*);
    void restartGame(const std::string&);
    void render()const override;
};

