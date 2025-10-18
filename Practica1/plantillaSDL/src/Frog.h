#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Frog {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_LastDir;
	int m_nHealth;

public:
	Frog(){}
	Frog(Game* game, Texture* texture, const Vector2D<float>& pos, int maxHealth = 3);
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&) const;
	void handleEvent(const SDL_Event&);
};
