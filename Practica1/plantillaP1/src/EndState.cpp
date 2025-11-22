#include "EndState.h"
#include "SDLApplication.h"
#include "Button.h"
#include <SDL3/SDL.h>

EndState::EndState(SDLApplication* g, bool victory)
    : GameState(g)
{
    Button* exit = new Button(this, m_pGame->getTexture(SDLApplication::SALIR), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::SALIR)->getFrameWidth() / 2),
                          (float)(380 - m_pGame->getTexture(SDLApplication::SALIR)->getFrameHeight())
        }
    );
    addObject(exit);
    exit->connect([this]() { m_pGame->popState(); m_pGame->popState(); });

    Button* volver = new Button(this, m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameWidth() / 2),
                          (float)(300 - m_pGame->getTexture(SDLApplication::VOLVER_AL_MENU)->getFrameHeight())
        }
    );
    addObject(volver);
    volver->connect([this]() { m_pGame->popState(); });
    SDL_Color victoryColor = { 0,255,0 };
    SDL_Color loseColor = { 255,0,0 };

    Label* title = new Label(this, m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER), {
                          (float)((SDLApplication::WINDOW_WIDTH / 2) - m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER)->getFrameWidth() / 2),
                          (float)(100 - m_pGame->getTexture(victory ? SDLApplication::HAS_GANADO : SDLApplication::GAME_OVER)->getFrameHeight())

        }, (victory ? victoryColor:loseColor));
    addObject(title);
}
