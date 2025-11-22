#pragma once

#include <list>
#include <functional>

#include "GameObject.h"
#include "SDL3/SDL.h"
#include "EventHandler.h"

class SDLApplication;

class GameState
{
    using DelayedCallback = std::function<void()>;

    std::list<GameObject*> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::list<DelayedCallback> delayedCallbacks;

protected:
    SDLApplication* m_pGame;

public:
    using Anchor = std::list<GameObject*>::iterator;

    GameState(SDLApplication*);
    virtual ~GameState();
    virtual void render() const;
    virtual void update();
    virtual void handleEvent(const SDL_Event&);
    void addEventListener(EventHandler*);
    GameState::Anchor addObject(GameObject*);
    void removeObject(GameState::Anchor);
    void runLater(DelayedCallback);
    SDLApplication* getSDLApplication() const;
};

