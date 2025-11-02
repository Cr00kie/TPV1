#include "Turtle.h"

#include "Log.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

TurtleGroup::TurtleGroup(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Platform(game, texture, pos, vel, Game::BAST * 2 + Game::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
}

TurtleGroup::TurtleGroup(Game* game, Texture* texture, std::istream& is)
	: Platform(game, texture, is, Game::BAST * 2 + Game::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
}

void TurtleGroup::render() const
{
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->renderFrame(pos, 0, m_nCurrFrame, SDL_FLIP_HORIZONTAL);
}

void TurtleGroup::update()
{
	m_fnextFrameTimer -= Game::DELTA;
	if (m_fnextFrameTimer <= 0)
	{
		m_nCurrFrame = (m_nCurrFrame + 1) % m_pTexture->getNumColumns();
		m_fnextFrameTimer = ANIM_PER;
	}

    Platform::update();
}

Collision TurtleGroup::checkCollision(SDL_FRect other)
{
    SDL_FRect rect = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&rect, &other))
		return m_nCurrFrame == 5 ? Collision(Collision::NONE) : Collision(Collision::PLATFORM, m_Vel);

	return Collision(Collision::NONE);
}
