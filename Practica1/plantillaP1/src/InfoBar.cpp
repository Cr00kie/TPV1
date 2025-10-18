#include "InfoBar.h"
#include "texture.h"
#include <SDL3/SDL.h>

InfoBar::InfoBar(Game* g, Texture* t, Vector2D<int> pos) : m_pGame(g), m_pTexture(t), m_Pos(pos)
{
}

void InfoBar::render(int vidas)
{
	SDL_FRect target = { m_Pos.getX(), m_Pos.getY(), m_pTexture->getFrameWidth(), m_pTexture->getFrameHeight()};
	
	for(int i = 0; i < vidas; ++i) 
	{
		target.x = m_Pos.getX() + i * target.w;
		m_pTexture->renderFrame(target,0,0);
	}
}
