#include "Turtle.h"

#include "Log.h"
#include "Collision.h"
#include "PlayState.h"

#include <string>
using namespace std::string_literals;

TurtleGroup::TurtleGroup(PlayState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Platform(game, texture, pos, vel, PlayState::BAST * 2 + SDLApplication::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0), m_bDive(false)
{
}

TurtleGroup::TurtleGroup(PlayState* game, Texture* texture, std::istream& is)
	: Platform(game, texture, is, PlayState::BAST * 2 + SDLApplication::WINDOW_WIDTH), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
    is >> m_nGroupSize >> m_bDive;
}

void TurtleGroup::render() const
{
    for (int i = 0; i < m_nGroupSize; ++i) {
	    SDL_FRect pos = getBoundingBox();
        pos.x = pos.x + pos.w * i;
	    m_pTexture->renderFrame(pos, 0, m_nCurrFrame, m_Vel.getX()>0?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
    }
}

void TurtleGroup::update()
{
    m_fnextFrameTimer -= SDLApplication::DELTA;
    if (m_fnextFrameTimer <= 0)
    {
        m_nCurrFrame = (m_nCurrFrame + 1) % (m_bDive?m_pTexture->getNumColumns():2);
        m_fnextFrameTimer = ANIM_PER;
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
