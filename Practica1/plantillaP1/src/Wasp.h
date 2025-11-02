#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "SceneObject.h"

class Game;
struct Collision;

class Wasp : public SceneObject{
private:
    using Anchor = std::list<SceneObject*>::iterator; // no me funciona Game::Anchor
	Vector2D<float> m_Vel;
	float m_nTiempoVida;
    Anchor m_Anchor;

public:
	Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida);
	void update();
	Collision checkCollision(SDL_FRect) override;
	bool isAlive() const;
    void SetAnchor(Anchor anchor);
};
