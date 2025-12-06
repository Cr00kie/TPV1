#pragma once

#include "SceneObject.h"
#include "vector2D.h"

struct Collision;

class Crosser : public SceneObject
{
protected:
    Vector2D<float> m_Vel;
    float m_fBackjump;

public:
    Crosser(PlayState* g, Texture* t, Vector2D<float> p, Vector2D<float> v, float b);
    Crosser(PlayState* g, Texture* t, std::istream&, float b);
    virtual ~Crosser() = default;
    void update() override;
};

