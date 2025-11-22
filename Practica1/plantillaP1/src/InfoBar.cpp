#include "InfoBar.h"
#include "texture.h"
#include <SDL3/SDL.h>
#include "GameState.h"

InfoBar::InfoBar(GameState* g, Texture* t, Vector2D<int> pos) : GameObject(g), m_pTexture(t), m_Pos(pos), m_nVidas(0)
{
}

void InfoBar::render() const
{
	SDL_FRect target = { (float)m_Pos.getX(), (float)m_Pos.getY(), (float)m_pTexture->getFrameWidth(), (float)m_pTexture->getFrameHeight()};
	for(int i = 0; i < m_nVidas; ++i) 
	{
		target.x = m_Pos.getX() + i * target.w;
		m_pTexture->renderFrame(target,0,0);
	}
}
