#include "Log.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

Log::Log(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel)
{
}

Log::Log(Game* game, Texture* texture, std::istream& is)
	: m_pGame(game), m_pTexture(texture)
{
	float x, y, vX;
	int type;
	is >> x >> y >> vX >> type;
	m_Pos.setX(x); m_Pos.setY(y);
	m_Vel.setX(vX);

	if (type < 0 || type > 1) throw "Error: no se ha podido leer log"s;

	m_pTexture = game->getTexture(Game::TextureName(Game::LOG1 + type));
}

void Log::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight())};
	m_pTexture->render(pos);
}

void Log::update() {
	m_Pos = m_Pos + m_Vel * m_pGame->DELTA;

	if (m_Pos.getX() < m_pGame->BAST_IZQ)
		m_Pos.setX(m_pGame->WINDOW_WIDTH + m_pGame->BAST_DER);
	else if (m_Pos.getX() > m_pGame->WINDOW_WIDTH + m_pGame->BAST_DER)
		m_Pos.setX(m_pGame->BAST_IZQ);
}

Collision Log::checkCollision(const SDL_FRect& other) const {
	int width = m_pTexture->getFrameWidth();
	int height = m_pTexture->getFrameHeight();
	int x = int(m_Pos.getX());
	int y = int(m_Pos.getY());

	SDL_FRect rect = { x, y, width, height };

	if(SDL_HasRectIntersectionFloat(&rect, &other))
		return Collision(Collision::PLATFORM, m_Vel);

	return Collision(Collision::NONE);
}
