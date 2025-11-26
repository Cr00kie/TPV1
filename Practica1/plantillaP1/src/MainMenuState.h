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
    Button* m_pRightArrow;
    Button* m_pLeftArrow;

public:
    MainMenuState(SDLApplication*);
    ~MainMenuState();

    void moveRight();
    void moveLeft();

    void updateArrows();

    void handleEvent(const SDL_Event& e) override;
};

