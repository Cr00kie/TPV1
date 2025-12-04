#include "MainMenuState.h"
#include "Label.h"
#include "Button.h"
#include "SDLApplication.h"
#include "gameStateMachine.h"
#include "PlayState.h"
#include <unordered_map>
#include <filesystem>
#include <fstream>

constexpr const char* const SAVE_FILE = "config.txt";

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game), m_nCurrentSelectedMap(0)
{
    addObject(new Label(this, m_pGame->getTexture(SDLApplication::MENU_BACKGROUND), { 0,0 }));

    std::ifstream configFile(SAVE_FILE);
    if (configFile.is_open())
        configFile >> m_nCurrentSelectedMap;

    addObject(new Label(this, m_pGame->getTexture(SDLApplication::ELIGE_UN_MAPA), {
          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::ELIGE_UN_MAPA)->getFrameWidth()/2),
          (float)(220 - m_pGame->getTexture(SDLApplication::ELIGE_UN_MAPA)->getFrameHeight())
        }));

    Button* exit = new Button(this, m_pGame->getTexture(SDLApplication::SALIR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::SALIR)->getFrameWidth() / 2),
                          (float)(EXIT_POS - m_pGame->getTexture(SDLApplication::SALIR)->getFrameHeight())
                        }
                    );
    addObject(exit);
    exit->connect([this]() { m_pGame->popState(); });

    m_pRightArrow = new Button(this, m_pGame->getTexture(SDLApplication::RIGHT), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) + ARROWS_DISTANCE/2 - m_pGame->getTexture(SDLApplication::RIGHT)->getFrameWidth() / 2),
                          (float)(LEVEL_POS - m_pGame->getTexture(SDLApplication::RIGHT)->getFrameHeight())
        }
    );
    addObject(m_pRightArrow);
    m_pRightArrow->connect([this]() { moveRight(); });

    m_pLeftArrow = new Button(this, m_pGame->getTexture(SDLApplication::LEFT), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - ARROWS_DISTANCE / 2 - m_pGame->getTexture(SDLApplication::LEFT)->getFrameWidth() / 2),
                          (float)(LEVEL_POS - m_pGame->getTexture(SDLApplication::LEFT)->getFrameHeight())
        }
    );
    addObject(m_pLeftArrow);
    m_pLeftArrow->connect([this]() { moveLeft(); });

    std::unordered_map<std::string, SDLApplication::TextureName> mapNameTextures({
        {"Avispado", SDLApplication::AVISPADO},
        {"Original", SDLApplication::ORIGINAL},
        {"Practica 1", SDLApplication::PRACTICA_1},
        {"Trivial", SDLApplication::TRIVIAL},
        {"Veloz", SDLApplication::VELOZ},
        });

    for (auto entry : std::filesystem::directory_iterator("../assets/maps"))
    {
        std::string mapName = entry.path().stem().string();
        m_maps.push_back(mapName);

        Button* levelButton = new Button(this, m_pGame->getTexture(mapNameTextures[mapName]), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(mapNameTextures[mapName])->getFrameWidth() / 2),
                          (float)(LEVEL_POS - m_pGame->getTexture(mapNameTextures[mapName])->getFrameHeight())
            }
        );
        levelButton->connect([this]() {
            m_pGame->pushState(new PlayState(m_pGame, m_maps[m_nCurrentSelectedMap]));
            //m_pGame->getSoundManager().play(SoundManager::GAMESTART);
            });
        levelButton->setActive(false);
        addObject(levelButton);
        m_mapsButtons.push_back(levelButton);
    }
    m_mapsButtons[m_nCurrentSelectedMap]->setActive(true);

    updateArrows();
}

MainMenuState::~MainMenuState()
{
    std::ofstream configFile(SAVE_FILE);
    configFile << m_nCurrentSelectedMap;
}

void
MainMenuState::handleEvent(const SDL_Event& e)
{
    GameState::handleEvent(e);
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
        switch (e.key.key)
        {
        case SDLK_RIGHT:
            moveRight();
            break;
        case SDLK_LEFT:
            moveLeft();
            break;
        case SDLK_RETURN:
            m_pGame->pushState(new PlayState(m_pGame, m_maps[m_nCurrentSelectedMap]));
            break;
        }
    }
}

void MainMenuState::moveRight() {
    if (m_nCurrentSelectedMap + 1 < m_mapsButtons.size())
    {
        m_mapsButtons[m_nCurrentSelectedMap]->setActive(false);
        ++m_nCurrentSelectedMap;
        m_mapsButtons[m_nCurrentSelectedMap]->setActive(true);
    }

    updateArrows();
}

void MainMenuState::moveLeft()
{
    if (m_nCurrentSelectedMap - 1 >= 0)
    {
        m_mapsButtons[m_nCurrentSelectedMap]->setActive(false);
        --m_nCurrentSelectedMap;
        m_mapsButtons[m_nCurrentSelectedMap]->setActive(true);
    }

    updateArrows();
}

void MainMenuState::updateArrows()
{
    m_pRightArrow->setActive(m_nCurrentSelectedMap + 1 < m_mapsButtons.size());
    m_pLeftArrow->setActive(m_nCurrentSelectedMap - 1 >= 0);
}
