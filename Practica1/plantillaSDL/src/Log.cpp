#include "Log.h"

Log::Log(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel)
{
}

void Log::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight())};
	m_pTexture->render(pos);
}

void Log::update() {
	m_Pos = m_Pos + m_Vel;

	if (m_Pos.getX() < -150)
		m_Pos = Vector2D<float>(598, m_Pos.getY());
}

bool Log::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	return (other.x > x && other.x < (x + width)) || ((other.x + other.w) > x && (other.x + other.w) < (x + width)    // Comprueba si solapan en el eje X
		&& (other.y > y && other.y < (y + height)) || ((other.y + other.h) > y && (other.y + other.h) < (y + height)) // Comprueba si solapan en el eje Y
		);
}
