#include "Frog.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include <cmath>
#include <numbers>

Frog::Frog(GameState* game, Texture* texture, const Vector2D<float>& pos, int maxHelath)
	: SceneObject(game, texture, pos), m_StartPos(pos), 
	  m_nHealth(maxHelath), m_LastDir(0,0), 
	  m_bMove(false), m_fAnimTime(0),
      m_fLiveTime(TIMER)
{}

Frog::Frog(GameState* game, Texture* texture, std::istream& is, int maxHealth)
	: SceneObject(game, texture, is, texture->getFrameWidth() - COLLIDER_REDUCTION, texture->getFrameHeight() - COLLIDER_REDUCTION),
	  m_nHealth(maxHealth), m_LastDir(0,0), 
	  m_bMove(false), m_fAnimTime(0),
      m_fLiveTime(TIMER)
{
	m_StartPos = m_Pos;
}

void Frog::render() const {
	SDL_FRect pos = { m_Pos.getX(), m_Pos.getY(), float(m_pTexture->getFrameWidth()), float(m_pTexture->getFrameHeight()) };
	m_pTexture->renderFrame(pos, 0, m_fAnimTime > 0, 360 * std::atan2(m_LastDir.getX(), -m_LastDir.getY()) / (2 * std::numbers::pi));
}

void Frog::update() {
	// Actualiza posicion por input
	if (m_bMove) {
		// Reinicia animacion
		m_fAnimTime = ANIM_DURATION;

        Vector2D<float> nextPos = m_Pos + (m_LastDir * STEP);

		// Comprueba que la rana este en los limites
        if (nextPos.getX() < 0) m_fAnimTime = 0;
		else if (nextPos.getX() > SDLApplication::WINDOW_WIDTH-STEP) m_fAnimTime = 0;
		
		if (nextPos.getY() < 0) m_fAnimTime = 0;
		else if (nextPos.getY() > PlayState::HUD_POS_Y-STEP) m_fAnimTime = 0;

        //Play sound
        m_pGame->getSDLApplication()->getSoundManager().play(SoundManager::JUMP);

		m_bMove = false;
	}

    if (m_fAnimTime > 0) {
        // Actualiza posicion
        m_Pos = m_Pos + (m_LastDir * (STEP / ANIM_DURATION)*SDLApplication::DELTA);
    }

	// Actualiza posicion por fisica
	m_Pos = m_Pos + (m_Vel * SDLApplication::DELTA);

	// Comprueba si la rana ha sido arrastrada fuera
	if (m_Pos.getX() < 0 || m_Pos.getY() < 0
		|| m_Pos.getX() > SDLApplication::WINDOW_WIDTH || m_Pos.getY() > SDLApplication::WINDOW_HEIGHT) {
		die();	
	}

	// Animacion
	m_fAnimTime -= SDLApplication::DELTA;
    m_fLiveTime -= SDLApplication::DELTA;
    if (m_fLiveTime <= 0) die();

    checkCollisions();
}

void Frog::handleEvent(const SDL_Event& event)
{
	if(event.type == SDL_EVENT_KEY_DOWN && m_fAnimTime <= 0){
		switch (event.key.key) {
			case SDLK_A: m_LastDir.setX(-1); m_LastDir.setY(0); m_bMove = true; break;
			case SDLK_W: m_LastDir.setX(0); m_LastDir.setY(-1); m_bMove = true; break;
			case SDLK_S: m_LastDir.setX(0); m_LastDir.setY(1); m_bMove = true; break;
			case SDLK_D: m_LastDir.setX(1); m_LastDir.setY(0); m_bMove = true; break;
		}	
	}
}

void Frog::checkCollisions()
{
    SDL_FRect box = getBoundingBox();
    // Buscamos colision
    Collision colData = m_pPlayState->checkCollision(getBoundingBox());

    // Realizamos accion correspondiente a dicha accion
    switch (colData.type) {
    case Collision::ENEMY:
        die();
        m_Vel = Vector2D<float>(0, 0);
        break;
    case Collision::PLATFORM:
        m_Vel = colData.vel;
        break;
    case Collision::HOME:
        resetFrog();
        break;
    case Collision::NONE:
        // Si cae al agua muere
        if (m_Pos.getY() < PlayState::RIVER_LOW - getBoundingBox().h)
            die();
        m_Vel = Vector2D<float>(0, 0);
    }
}

int Frog::getFrogHealth() const
{
	return m_nHealth;
}

float Frog::getFrogLiveTime() const
{
    return m_fLiveTime;
}

void Frog::die()
{
	resetFrog();
	--m_nHealth;
	if (m_nHealth <= 0) m_pPlayState->endGame(true);
}

void Frog::resetFrog()
{
	m_Pos = m_StartPos;
	m_Vel = m_Vel * 0;
    m_fAnimTime = 0;
    m_fLiveTime = TIMER;
    m_bMove = false;
}

SDL_FRect Frog::getBoundingBox() const { return SDL_FRect(m_Pos.getX()+COLLIDER_REDUCTION, m_Pos.getY()+COLLIDER_REDUCTION, m_nWidth-COLLIDER_REDUCTION*2, m_nHeight-COLLIDER_REDUCTION*2); }


