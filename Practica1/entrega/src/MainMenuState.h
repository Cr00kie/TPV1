#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>

class Button;

class MainMenuState :
    public GameState
{
    static constexpr float TITLE_POS = 220;
    static constexpr float LEVEL_POS = 300;
    static constexpr float EXIT_POS = 380;
    // Distancia entre las dos flechas
    static constexpr float ARROWS_DISTANCE = 250;
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

