#pragma once
#include "GameState.h"
class EndState :
    public GameState
{

    static constexpr float TITLE_BUT_POS = 100;
    static constexpr float EXIT_BUT_POS = 380;
    static constexpr float RETU_BUT_POS = 300;
    static constexpr SDL_Color VICTORY_COLOR = { 0,255,0 };
    static constexpr SDL_Color LOSE_COLOR = { 255,0,0 };
public:
    EndState(SDLApplication*, bool victory);
};

