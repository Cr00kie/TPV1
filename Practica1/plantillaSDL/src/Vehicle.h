#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Vehicle {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_Vel;

public:
	Vehicle(){}
	Vehicle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel );
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&) const;
};
