#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Wasp {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_Vel;
	int m_nTiempoVida;

public:
	Wasp(){}
	Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, int tiempoVida);
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&) const;
	bool isAlive();
};
