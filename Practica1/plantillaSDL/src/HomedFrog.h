#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class HomedFrog {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;

public:
	HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos);
	void render() const;
	void update();
	bool checkCollision(const SDL_FRect&) const;
};
