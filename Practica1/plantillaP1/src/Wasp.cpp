#include "Wasp.h"
#include "Collision.h"

Wasp::Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel), m_nTiempoVida(tiempoVida)
{}

void Wasp::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->render(pos);
}

void Wasp::update() {
	m_nTiempoVida -= m_pGame->DELTA;
}

Collision Wasp::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	SDL_FRect rect = { x, y, width, height };
	Collision ret;

	if (SDL_HasRectIntersectionFloat(&rect, &other))
	{
		ret.type = ret.ENEMY;
	}
	else {
		ret.type = ret.NONE;
	}

	return ret;
}

bool Wasp::isAlive()
{
	return m_nTiempoVida > 0;
}
