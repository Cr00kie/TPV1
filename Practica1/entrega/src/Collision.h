#pragma once
#include "vector2D.h"

struct Collision {
	enum Type {
		NONE,
		ENEMY,
		PLATFORM,
		HOME,
	};
	Type type;
	Vector2D<float> vel;
};