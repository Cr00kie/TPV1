#pragma once
#include "GameError.h"
#include "SDL3/SDL.h"

class SDLError : public GameError
{
public:
    SDLError() : GameError(SDL_GetError()){}
};

