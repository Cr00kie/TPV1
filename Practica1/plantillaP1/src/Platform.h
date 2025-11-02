#pragma once
#include "Crosser.h"

class Platform : public Crosser
{
    using Crosser::Crosser;
    Collision checkCollision(SDL_FRect other) override;
};

