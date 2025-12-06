#pragma once
#include "texture.h"
#include "vector2D.h"
#include "Platform.h"

class GameState;
struct Collision;

class Log : public Platform{
public:
	Log(PlayState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	Log(PlayState* game, Texture* texture, std::istream& is);
};
