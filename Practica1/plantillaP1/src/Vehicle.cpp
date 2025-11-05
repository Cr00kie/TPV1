#include "Vehicle.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

Vehicle::Vehicle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Crosser(game, texture, pos, vel, Game::BAST+Game::WINDOW_WIDTH)
{}

Vehicle::Vehicle(Game * game, Texture * texture, std::istream & is)
	: Crosser(game, texture, is, Game::BAST + Game::WINDOW_WIDTH + texture->getFrameWidth())
{
	int type;
	is >> type;

	//if (type < 1 || type > 5) throw "Error: no se ha podido leer un coche"s;

	m_pTexture = game->getTexture(Game::TextureName(game->CAR1 + (type - 1)));
}

Collision Vehicle::checkCollision(SDL_FRect other) {
    SDL_FRect rect = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&rect, &other))
		return Collision(Collision::ENEMY);
	
	return Collision(Collision::NONE);
}
