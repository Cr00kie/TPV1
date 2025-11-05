#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Platform.h"


class Game;
struct Collision;

int constexpr ANIM_FPS = 4;
float constexpr ANIM_PER = 1.f/ANIM_FPS;

class TurtleGroup : public Platform
{
private:
	float m_fnextFrameTimer;
	int m_nCurrFrame;
    bool m_bDive;
    int m_nGroupSize;

public:
	TurtleGroup(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	TurtleGroup(Game* game, Texture* texture, std::istream& is);
	void render() const;
	void update();
	Collision checkCollision(SDL_FRect) override;
};

