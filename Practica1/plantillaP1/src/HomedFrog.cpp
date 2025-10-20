#include "HomedFrog.h"

HomedFrog::HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_bIsActive(false)
{}

void HomedFrog::render() const {
	if (m_bIsActive)
	{
		SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
		m_pTexture->renderFrame(pos, 0, 0);
	}
}

Collision HomedFrog::checkCollision(const SDL_FRect& other) const {
    float width = (float)m_pTexture->getFrameWidth();
    float height = (float)m_pTexture->getFrameHeight();
    float x = (float)m_Pos.getX();
    float y = (float)m_Pos.getY();

	SDL_FRect rect = { x, y, width, height };
	Collision ret;

	if (SDL_HasRectIntersectionFloat(&rect, &other))
	{
		ret.type = m_bIsActive ? ret.ENEMY : ret.HOME;
	}
	else {
		ret.type = ret.NONE;
	}

	return ret;
}

void HomedFrog::update() {}

bool HomedFrog::IsActive() const
{
	return m_bIsActive;
}

void HomedFrog::SetActive()
{
	m_bIsActive = true;
}
