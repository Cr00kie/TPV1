#include "GameState.h"
#include "SDLApplication.h"

GameState::GameState(SDLApplication* game)
    : m_pGame(game){}

GameState::~GameState()
{
    for (GameObject* go : gameObjects) delete go;
}

void
GameState::render() const
{
    for (auto it = gameObjects.rbegin(); it != gameObjects.rend(); ++it)
        (*it)->render();
}

void
GameState::update()
{
    for (GameObject* go : gameObjects) go->update();
    for (DelayedCallback callback : delayedCallbacks) callback();
    delayedCallbacks.clear();
}

void
GameState::handleEvent(const SDL_Event& event)
{
    for (EventHandler* handler : eventHandlers) handler->handleEvent(event);
}

void GameState::addEventListener(EventHandler* handler)
{
    eventHandlers.push_back(handler);
}

GameState::Anchor GameState::addObject(GameObject* go)
{
    gameObjects.push_front(go);
    return gameObjects.begin();
}

void GameState::removeObject(GameState::Anchor it)
{
    delete (*it);
    gameObjects.erase(it);
}

void GameState::runLater(DelayedCallback callback)
{
    delayedCallbacks.push_back(callback);
}

SDLApplication* GameState::getSDLApplication() const
{
    return m_pGame;
}
