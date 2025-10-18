#include "Wasp.h"

Wasp::Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, int tiempoVida)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel), m_nTiempoVida(tiempoVida)
{}

void Wasp::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->render(pos);
}

void Wasp::update() {
	//TODO
}

bool Wasp::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	return (other.x > x && other.x < (x + width)) || ((other.x + other.w) > x && (other.x + other.w) < (x + width)    // Comprueba si solapan en el eje X
		&& (other.y > y && other.y < (y + height)) || ((other.y + other.h) > y && (other.y + other.h) < (y + height)) // Comprueba si solapan en el eje Y
		);
}

bool Wasp::isAlive()
{
	return m_nTiempoVida > 0;
}
