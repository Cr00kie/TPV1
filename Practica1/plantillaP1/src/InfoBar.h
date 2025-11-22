#pragma once

#include "vector2D.h"
#include "GameObject.h"

class Texture;
class InfoBar : public GameObject
{
	Texture* m_pTexture;
	Vector2D<int> m_Pos;
    int m_nVidas;
public:
	InfoBar(GameState*, Texture*, Vector2D<int>);
	void render() const override;
    void update() override {}
    void updateVidas(int vidas) { m_nVidas = vidas; }
};

