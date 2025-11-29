#pragma once

class GameState;

class GameObject
{
protected:
    GameState* m_pGame;
    GameObject(GameState*);
public:
    virtual ~GameObject() = default;
    virtual void render() const = 0;
    virtual void update() = 0;
};

