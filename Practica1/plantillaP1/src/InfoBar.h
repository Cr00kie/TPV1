#pragma once

#include "vector2D.h"
class Game;
class Texture;
class InfoBar
{
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<int> m_Pos;
public:
	InfoBar(Game*, Texture*, Vector2D<int>);
	void render(int);
};

