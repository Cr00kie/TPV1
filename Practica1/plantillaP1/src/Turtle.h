#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"


class Game;
struct Collision;

int constexpr ANIM_FPS = 4;
float constexpr ANIM_PER = 1.f/ANIM_FPS;

class Turtle
{
private:
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
	Vector2D<float> m_Vel;
	float m_fnextFrameTimer;
	int m_nCurrFrame;

public:
	Turtle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	Turtle(Game* game, Texture* texture, std::istream& is);
	void render() const;
	void update();
	Collision checkCollision(const SDL_FRect&) const;
};

