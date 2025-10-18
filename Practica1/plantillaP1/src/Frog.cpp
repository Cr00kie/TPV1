#include "Frog.h"
#include <cmath>

Frog::Frog(Game* game, Texture* texture, const Vector2D<float>& pos, int maxHelath)
	: m_pGame(game), m_pTexture(texture), 
	  m_Pos(pos), m_StartPos(m_Pos), 
	  m_nHealth(maxHelath), m_LastDir(0,0), 
	  m_Vel(0,0), m_bMove(false) {}

Frog::Frog(Game* game, Texture* texture, std::istream& is, int maxHealth)
	: m_pGame(game), m_pTexture(texture), 
	  m_nHealth(maxHealth), m_LastDir(0,0), 
	  m_Vel(0,0), m_bMove(false)
{
	float x, y;
	is >> x >> y;
	m_Pos.setX(x);
	m_Pos.setY(y);
	m_StartPos = m_Pos;
}

void Frog::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->renderFrame(pos, 0, m_fAnimTime > 0, 360 * std::atan2(m_LastDir.getX(), -m_LastDir.getY()) / (2 * 3.14159));
}

void Frog::update() {
	// Actualiza posicion por input
	if (m_bMove) {
		// Reinicia animacion
		m_fAnimTime = ANIM_DURATION;
		
		// Actualiza posicion
		m_Pos = m_Pos + (m_LastDir * STEP);

		// Comprueba que la rana este en los limites
		if (m_Pos.getX() < 0) m_Pos.setX(m_Pos.getX() + STEP);
		else if (m_Pos.getX() > m_pGame->WINDOW_WIDTH-STEP) m_Pos.setX(m_Pos.getX() - STEP);
		
		if (m_Pos.getY() < 0) m_Pos.setY(m_Pos.getY() + STEP);
		else if (m_Pos.getY() > m_pGame->HUD_POS_Y-STEP) m_Pos.setY(m_Pos.getY() - STEP);

		m_bMove = false;
	}

	// Actualiza posicion por fisica
	m_Pos = m_Pos + (m_Vel * m_pGame->DELTA);

	// Comprueba si la rana ha sido arrastrada fuera
	if (m_Pos.getX() < 0 || m_Pos.getY() < 0
		|| m_Pos.getX() > m_pGame->WINDOW_WIDTH || m_Pos.getY() > m_pGame->WINDOW_HEIGHT) {
		die();	
	}

	// Animacion
	m_fAnimTime -= m_pGame->DELTA;
}

void Frog::handleEvent(const SDL_Event& event)
{
	if(event.type == SDL_EVENT_KEY_DOWN){
		switch (event.key.key) {
			case SDLK_A: m_LastDir.setX(-1); m_LastDir.setY(0); m_bMove = true; break;
			case SDLK_W: m_LastDir.setX(0); m_LastDir.setY(-1); m_bMove = true; break;
			case SDLK_S: m_LastDir.setX(0); m_LastDir.setY(1); m_bMove = true; break;
			case SDLK_D: m_LastDir.setX(1); m_LastDir.setY(0); m_bMove = true; break;
		}	
	}
}

const SDL_FRect Frog::getCollider() const
{
	return SDL_FRect(m_Pos.getX() + COLLIDER_REDUCTION, m_Pos.getY() + COLLIDER_REDUCTION, float(m_pTexture->getFrameWidth() - COLLIDER_REDUCTION*2), float(m_pTexture->getFrameHeight() - COLLIDER_REDUCTION*2));
}

const Vector2D<float>& Frog::getFrogPos() const
{
	return m_Pos;
}

int Frog::getFrogHealth() const
{
	return m_nHealth;
}

void Frog::setVelocity(Vector2D<float> vel)
{
	m_Vel = vel;
}

void Frog::die()
{
	resetPos();
	--m_nHealth;
	if (m_nHealth <= 0) m_pGame->endGame(true);
}

void Frog::resetPos()
{
	m_Pos = m_StartPos;
	m_Vel = m_Vel * 0;
}


