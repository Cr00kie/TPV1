#pragma once

class Game;

class GameObject
{
protected:
    Game* m_pGame;
    GameObject(Game*);
public:
    virtual ~GameObject() = default;
    virtual void render() const = 0;
    virtual void update() = 0;
};

