#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "Platform.h"


class Game;
struct Collision;

class Log : public Platform{
public:
	Log(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	Log(Game* game, Texture* texture, std::istream& is);
};
