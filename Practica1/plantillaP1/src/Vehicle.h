#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Crosser.h"


class Game;
struct Collision;

class Vehicle : public Crosser {
public:
	Vehicle(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel );
	Vehicle(Game* game, Texture* texture, std::istream& is);
	Collision checkCollision(SDL_FRect);
};
