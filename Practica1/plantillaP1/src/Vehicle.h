#pragma once
#include "SDLApplication.h"
#include "texture.h"
#include "vector2D.h"
#include "Crosser.h"


class SDLApplication;
struct Collision;

class Vehicle : public Crosser {
public:
	Vehicle(PlayState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel );
	Vehicle(PlayState* game, Texture* texture, std::istream& is);
	Collision checkCollision(SDL_FRect);
};
