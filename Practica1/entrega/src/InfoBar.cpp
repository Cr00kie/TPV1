#include "InfoBar.h"
#include "texture.h"
#include <SDL3/SDL.h>
#include "GameState.h"
#include "SDLApplication.h"
#include "Frog.h"

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
    SDL_FRect progressBar = { SDLApplication::WINDOW_WIDTH-TIMER_BAR_WIDTH, (float)m_Pos.getY()+5, TIMER_BAR_WIDTH * (m_fTimer / Frog::TIMER), TIMER_BAR_HEIGHT};
    SDL_SetRenderDrawColor(m_pGame->getSDLApplication()->getRenderer(), 255 * (1-m_fTimer / Frog::TIMER), 255*(m_fTimer / Frog::TIMER), 0, 255);
    SDL_RenderFillRect(m_pGame->getSDLApplication()->getRenderer(), &progressBar);
    SDL_SetRenderDrawColor(m_pGame->getSDLApplication()->getRenderer(), 255, 255, 255, 255);
    SDL_RenderRect(m_pGame->getSDLApplication()->getRenderer(), &progressBar);
    SDL_SetRenderDrawColor(m_pGame->getSDLApplication()->getRenderer(), 0, 0, 0, 255);
}
