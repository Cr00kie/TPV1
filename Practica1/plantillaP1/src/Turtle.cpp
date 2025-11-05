#include "Turtle.h"

#include "Log.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

TurtleGroup::TurtleGroup(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Platform(game, texture, pos, vel, Game::BAST * 2 + Game::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0), m_bDive(false)
{
}

TurtleGroup::TurtleGroup(Game* game, Texture* texture, std::istream& is)
	: Platform(game, texture, is, Game::BAST * 2 + Game::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
    is >> m_nGroupSize >> m_bDive;
}

void TurtleGroup::render() const
{
    for (int i = 0; i < m_nGroupSize; ++i) {
	    SDL_FRect pos = getBoundingBox();
        pos.x = pos.x + pos.w * i;
	    m_pTexture->renderFrame(pos, 0, m_nCurrFrame, SDL_FLIP_HORIZONTAL);
    }
}

void TurtleGroup::update()
{
    if (m_bDive) {
        m_fnextFrameTimer -= Game::DELTA;
        if (m_fnextFrameTimer <= 0)
        {
            m_nCurrFrame = (m_nCurrFrame + 1) % m_pTexture->getNumColumns();
            m_fnextFrameTimer = ANIM_PER;
        }
    }

    Platform::update();
}

Collision TurtleGroup::checkCollision(SDL_FRect other)
{
    SDL_FRect rect = getBoundingBox();
    rect.w *= m_nGroupSize;

    if (SDL_HasRectIntersectionFloat(&rect, &other))
		return m_nCurrFrame == 5 && m_bDive ? Collision(Collision::NONE) : Collision(Collision::PLATFORM, m_Vel);

	return Collision(Collision::NONE);
}
