#include "Turtle.h"

#include "Log.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

Turtle::Turtle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
}

Turtle::Turtle(Game* game, Texture* texture, std::istream& is)
	: m_pGame(game), m_pTexture(texture), m_fnextFrameTimer(ANIM_PER), m_nCurrFrame(0)
{
	float x, y, vX;
	is >> x >> y >> vX;
	m_Pos.setX(x); m_Pos.setY(y);
	m_Vel.setX(vX);

	m_pTexture = game->getTexture(Game::TextureName(Game::TURTLE));
}

void Turtle::render() const
{
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->renderFrame(pos, 0, m_nCurrFrame);
}

void Turtle::update()
{
	m_Pos = m_Pos + m_Vel * m_pGame->DELTA;

	m_fnextFrameTimer -= m_pGame->DELTA;
	if (m_fnextFrameTimer <= 0)
	{
		m_nCurrFrame = (m_nCurrFrame + 1) % 7;
		m_fnextFrameTimer = ANIM_PER;
	}


	if (m_Pos.getX() < m_pGame->BAST_IZQ)
		m_Pos.setX(m_pGame->WINDOW_WIDTH + m_pGame->BAST_DER);
	else if (m_Pos.getX() > m_pGame->WINDOW_WIDTH + m_pGame->BAST_DER)
		m_Pos.setX(m_pGame->BAST_IZQ);
}

Collision Turtle::checkCollision(const SDL_FRect& other) const
{
    float width = (float)m_pTexture->getFrameWidth();
    float height = (float)m_pTexture->getFrameHeight();
    float x = (float)m_Pos.getX();
    float y = (float)m_Pos.getY();

	SDL_FRect rect = { x, y, width, height };

	if (SDL_HasRectIntersectionFloat(&rect, &other))
		return m_nCurrFrame == 5 ? Collision(Collision::NONE) : Collision(Collision::PLATFORM, m_Vel);

	return Collision(Collision::NONE);
}
