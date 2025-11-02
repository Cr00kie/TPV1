#include "HomedFrog.h"

HomedFrog::HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos)
	: SceneObject(game, texture, pos), m_bIsActive(false)
{}

void HomedFrog::render() const {
	if (m_bIsActive)
	{
		m_pTexture->renderFrame(getBoundingBox(), 0, 0);
	}
}

// No lo hago const porque debe ser capaz de activarse si colisiona con la rana
Collision HomedFrog::checkCollision(SDL_FRect other) {
	Collision ret;
    SDL_FRect rect = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&rect, &other))
	{
		ret.type = m_bIsActive ? ret.ENEMY : ret.HOME;
        SetActive();
	}
	else {
		ret.type = ret.NONE;
	}

	return ret;
}

void HomedFrog::update() {}

bool HomedFrog::IsActive() const
{
	return m_bIsActive;
}

void HomedFrog::SetActive()
{
	m_bIsActive = true;
    m_pGame->occupyNest();
}
