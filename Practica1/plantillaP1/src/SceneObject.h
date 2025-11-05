#pragma once

#include "GameObject.h"
#include "vector2D.h"
#include "SDL3/SDL.h"
#include "texture.h"

struct Collision;

class SceneObject : public GameObject
{
protected:
    Vector2D<float> m_Pos;
    float m_nWidth, m_nHeight;
    Texture* m_pTexture;

    virtual SDL_FRect getBoundingBox() const;

public:
    SceneObject(Game*, Texture*, Vector2D<float>, float = -1.f, float = -1.f);
    SceneObject(Game*, Texture*, std::istream&, float = -1.f, float = -1.f);
    virtual ~SceneObject() = default;
    virtual Collision checkCollision(SDL_FRect other) = 0;
    void render() const override;
    virtual void update() = 0;
};

