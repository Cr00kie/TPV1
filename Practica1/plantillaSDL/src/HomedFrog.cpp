#include "HomedFrog.h"

HomedFrog::HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos)
{}

void HomedFrog::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->render(pos);
}

void HomedFrog::update() {}

bool HomedFrog::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	return (other.x > x && other.x < (x + width)) || ((other.x + other.w) > x && (other.x + other.w) < (x + width)    // Comprueba si solapan en el eje X
		&& (other.y > y && other.y < (y + height)) || ((other.y + other.h) > y && (other.y + other.h) < (y + height)) // Comprueba si solapan en el eje Y
		);
}
