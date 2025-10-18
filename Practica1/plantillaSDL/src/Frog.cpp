#include "Frog.h"

Frog::Frog(Game* game, Texture* texture, const Vector2D<float>& pos, int maxHelath)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_nHealth(maxHelath), m_LastDir(0,0)
{}

void Frog::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->renderFrame(pos, 0, 0);
}

void Frog::update() {
	m_Pos = m_Pos + (m_LastDir * 36);
	m_LastDir = m_LastDir * 0;
}

bool Frog::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	return (other.x > x && other.x < (x + width)) || ((other.x + other.w) > x && (other.x + other.w) < (x + width)    // Comprueba si solapan en el eje X
		&& (other.y > y && other.y < (y + height)) || ((other.y + other.h) > y && (other.y + other.h) < (y + height)) // Comprueba si solapan en el eje Y
		);
}

void Frog::handleEvent(const SDL_Event& event)
{
	if(event.type == SDL_EVENT_KEY_DOWN){
		switch (event.key.key) {
		case SDLK_A: m_LastDir.setX(-1); m_LastDir.setY(0); break;
		case SDLK_W: m_LastDir.setX(0); m_LastDir.setY(-1); break;
		case SDLK_S: m_LastDir.setX(0); m_LastDir.setY(1); break;
		case SDLK_D: m_LastDir.setX(1); m_LastDir.setY(0); break;
		}
	}
}
