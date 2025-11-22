#include "Wasp.h"
#include "Collision.h"
#include "SDLApplication.h"
#include <fstream>
#include <numbers>

Wasp::Wasp(GameState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida)
	: SceneObject(game, texture, pos), m_Vel(vel), m_fTiempoVida(tiempoVida)
{}

Wasp::Wasp(GameState * game, Texture * texture, std::istream & is)
    : SceneObject(game, texture, is)
{
    float vX, vY;
    is >> vX >> vY >> m_fTiempoVida;
    m_Vel.setX(vX);
    m_Vel.setY(vY);
}

void Wasp::update() {
    m_Pos = m_Pos + m_Vel * SDLApplication::DELTA;

	m_fTiempoVida -= SDLApplication::DELTA;

    if (m_fTiempoVida <= 0) m_pGame->runLater([this]() {
        m_pPlayState->removeObject(m_PlayStateAnchor);
        m_pGame->removeObject(m_GameStateAnchor);
        });
}

void Wasp::render() const
{
    m_pTexture->render(getBoundingBox(), 360 * std::atan2(m_Vel.getX(), -m_Vel.getY()) / (2 * std::numbers::pi));
}

Collision Wasp::checkCollision(SDL_FRect other) {
	Collision ret;
    SDL_FRect rect = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&rect, &other))
	{
		ret.type = ret.ENEMY;
	}
	else {
		ret.type = ret.NONE;
	}

	return ret;
}

bool Wasp::isAlive() const
{
	return m_fTiempoVida > 0;
}

void Wasp::SetGameStateAnchor(GameState::Anchor anchor)
{
    m_GameStateAnchor = anchor;
}
void Wasp::SetPlayStateAnchor(PlayState::Anchor anchor)
{
    m_PlayStateAnchor = anchor;
}
