#include "PauseState.h"
#include "SDLApplication.h"
#include "Button.h"
#include "PlayState.h"

PauseState::PauseState(SDLApplication* g, PlayState* playState)
    : GameState(g), m_pPlayState(playState)
{
    Button* contin = new Button(this, m_pGame->getTexture(SDLApplication::CONTINUAR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::CONTINUAR)->getFrameWidth() / 2),
                          (float)(100 - m_pGame->getTexture(SDLApplication::CONTINUAR)->getFrameHeight())
        }
    );
    addObject(contin);
    contin->connect([this]() { m_pGame->popState(); });

    Button* restart = new Button(this, m_pGame->getTexture(SDLApplication::REINICIAR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::REINICIAR)->getFrameWidth() / 2),
                          (float)(200 - m_pGame->getTexture(SDLApplication::REINICIAR)->getFrameHeight())
        }
    );
    addObject(restart);
    restart->connect([this]() { restartGame(m_pPlayState->getMapName()); });

    Button* volver = new Button(this, m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameWidth() / 2),
                          (float)(300 - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameHeight())
        }
    );
    addObject(volver);
    volver->connect([this]() { m_pGame->popState(); m_pGame->popState(); });

    Button* exit = new Button(this, m_pGame->getTexture(SDLApplication::SALIR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::SALIR)->getFrameWidth() / 2),
                          (float)(400 - m_pGame->getTexture(SDLApplication::SALIR)->getFrameHeight())
        }
    );
    addObject(exit);
    exit->connect([this]() { m_pGame->popState(); m_pGame->popState(); m_pGame->popState();});

    m_pGame->getSoundManager().play(SoundManager::PAUSE);
}

void PauseState::restartGame(const std::string& mapName)
{
    const SDL_MessageBoxButtonData buttons[] = {
                {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel"},
                {0, 1, "Accept"},
    };
    SDL_MessageBoxData boxData = {
        SDL_MESSAGEBOX_INFORMATION,
        m_pGame->getWindow(),
        "Restarting game",
        "Are you sure you want to restart the game?",
        2,
        buttons
    };
    int button;
    SDL_ShowMessageBox(&boxData, &button);
    if (button == 1)
    {
        m_pGame->popState();
        m_pGame->replaceState(new PlayState(m_pGame, mapName));
        m_pGame->getSoundManager().play(SoundManager::GAMESTART);
    }
}

void PauseState::render() const
{
    m_pPlayState->render();

    SDL_SetRenderDrawColor(m_pGame->getRenderer(), 0,0,0,128);
    SDL_FRect overlay = { 0,0,SDLApplication::WINDOW_WIDTH,SDLApplication::WINDOW_HEIGHT };
    SDL_RenderFillRect(m_pGame->getRenderer(), &overlay);
    for (GameObject* go : gameObjects) go->render();
}
