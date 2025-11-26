#pragma once

#include "vector2D.h"
#include "GameObject.h"

class Texture;
class InfoBar : public GameObject
{
    static constexpr float TIMER_BAR_WIDTH = 250.f;
    static constexpr float TIMER_BAR_HEIGHT= 25.f;

	Texture* m_pTexture;
	Vector2D<int> m_Pos;
    int m_nVidas;
    float m_fTimer;
public:
	InfoBar(GameState*, Texture*, Vector2D<int>);
	void render() const override;
    void update() override {}
    void updateVidas(int vidas) { m_nVidas = vidas; }
    void updateTimer(float time) { m_fTimer = time; }
};

