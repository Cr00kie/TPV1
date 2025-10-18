#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"


class Game;
struct Collision;

class Wasp {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_Vel;
	float m_nTiempoVida;

public:
	Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida);
	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect&) const;
	bool isAlive();
};
