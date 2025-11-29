#include "EndState.h"
#include "SDLApplication.h"
#include "Button.h"
#include <SDL3/SDL.h>

EndState::EndState(SDLApplication* g, bool victory)
    : GameState(g)
{
    Button* exit = new Button(this, m_pGame->getTexture(SDLApplication::SALIR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::SALIR)->getFrameWidth() / 2),
                          (float)(EXIT_BUT_POS - m_pGame->getTexture(SDLApplication::SALIR)->getFrameHeight())
        }
    );
    addObject(exit);
    exit->connect([this]() { m_pGame->popState(); m_pGame->popState(); });

    Button* volver = new Button(this, m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameWidth() / 2),
                          (float)(RETU_BUT_POS - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameHeight())
        }
    );
    addObject(volver);
    volver->connect([this]() { m_pGame->popState(); });

    Label* title = new Label(this, m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER)->getFrameWidth() / 2),
                          (float)(TITLE_BUT_POS - m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER)->getFrameHeight())

        }, (victory ? VICTORY_COLOR:LOSE_COLOR));
    addObject(title);

    m_pGame->getSoundManager().play((victory ? SoundManager::WIN : SoundManager::GAMEOVER));
}
