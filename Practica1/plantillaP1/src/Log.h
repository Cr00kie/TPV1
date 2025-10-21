#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"


class Game;
struct Collision;

class Log {
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_Vel;

public:
	Log(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	Log(Game* game, Texture* texture, std::istream& is);
	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect&) const;
};
