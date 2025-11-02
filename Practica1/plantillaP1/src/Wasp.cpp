#include "Wasp.h"
#include "Collision.h"

Wasp::Wasp(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida)
	: SceneObject(game, texture, pos), m_Vel(vel), m_nTiempoVida(tiempoVida)
{}

void Wasp::update() {
	m_nTiempoVida -= Game::DELTA;

    if (m_nTiempoVida <= 0) m_pGame->deleteAfter(m_Anchor);
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
	return m_nTiempoVida > 0;
}

void Wasp::SetAnchor(Game::Anchor anchor)
{
    m_Anchor = anchor;
}
