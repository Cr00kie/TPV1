#include "Vehicle.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

Vehicle::Vehicle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: m_pGame(game), m_pTexture(texture), m_Pos(pos), m_Vel(vel)
{}

Vehicle::Vehicle(Game * game, Texture * texture, std::istream & is)
	: m_pGame(game), m_pTexture(texture)
{
	float x, y, vX;
	int type;
	is >> x >> y >> vX >> type;
	m_Pos.setX(x); m_Pos.setY(y);
	m_Vel.setX(vX);

	if (type < 1 || type > 5) throw "Error: no se ha podido leer un coche"s;

	m_pTexture = game->getTexture(Game::TextureName(game->CAR1 + (type - 1)));
}

void Vehicle::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight())};
	m_pTexture->render(pos);
}

void Vehicle::update() {
	m_Pos = m_Pos + m_Vel * Game::DELTA;

	if (m_Pos.getX() < Game::BAST_IZQ)
		m_Pos.setX(Game::WINDOW_WIDTH);
	else if (m_Pos.getX() > Game::WINDOW_WIDTH + Game::BAST_DER)
		m_Pos.setX(-(float)m_pTexture->getFrameWidth());
}

Collision Vehicle::checkCollision(const SDL_FRect& other) const {

	SDL_FRect rect = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
		
	if (SDL_HasRectIntersectionFloat(&rect, &other))
		return Collision(Collision::ENEMY);
	
	return Collision(Collision::NONE);
}
