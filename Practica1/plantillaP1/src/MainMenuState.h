#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>

class Button;

class MainMenuState :
    public GameState
{
    std::vector<Button*> m_mapsButtons;
    std::vector<std::string> m_maps;
    int m_nCurrentSelectedMap;
public:
    MainMenuState(SDLApplication*);
    ~MainMenuState();

    void handleEvent(const SDL_Event& e) override;
};

