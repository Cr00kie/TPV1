#include "Platform.h"
#include "Collision.h"

Collision Platform::checkCollision(SDL_FRect other)
{
    SDL_FRect rect = getBoundingBox();
    if (SDL_HasRectIntersectionFloat(&rect, &other))
        return Collision(Collision::PLATFORM, m_Vel);
    return Collision(Collision::NONE);
}
