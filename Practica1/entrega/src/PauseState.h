#pragma once
#include "GameState.h"
#include <string>

class PlayState;

class PauseState :
    public GameState
{
    static constexpr float CONT_BUT_POS = 100;
    static constexpr float REST_BUT_POS = 200;
    static constexpr float RETU_BUT_POS = 300;
    static constexpr float EXIT_BUT_POS = 400;
    PlayState* m_pPlayState;
public:
    PauseState(SDLApplication*, PlayState*);
    void restartGame(const std::string&);
    void render()const override;
};

