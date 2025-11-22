#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "texture.h"
#include <SDL3/SDL.h>

class Label :
    public GameObject
{
protected:
    Vector2D<float> m_Pos;
    Texture* m_pTexture;
    SDL_Color m_textColor;

public:
    Label(GameState*, Texture*, Vector2D<float>, SDL_Color textColor = {255,255,255});
    virtual ~Label() = default;
    void render() const override;
    void update() override;
};

