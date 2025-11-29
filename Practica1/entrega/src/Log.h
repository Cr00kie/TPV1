#pragma once
#include "texture.h"
#include "vector2D.h"
#include "Platform.h"

class GameState;
struct Collision;

class Log : public Platform{
public:
	Log(GameState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel);
	Log(GameState* game, Texture* texture, std::istream& is);
};
