#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Game;
struct Collision;

class HomedFrog {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	bool m_bIsActive;

public:
	HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos);
	void render() const;
    // No lo hago const porque debe ser capaz de activarse si colisiona con la rana
	Collision checkCollision(const SDL_FRect&);
	void update();
	bool IsActive() const;
	void SetActive();
};
