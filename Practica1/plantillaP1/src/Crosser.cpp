#include "Crosser.h"
#include "SDLApplication.h"
#include "PlayState.h"

Crosser::Crosser(PlayState* g, Texture* t, Vector2D<float> p, Vector2D<float> v, float backjump) : SceneObject(g, t, p), m_Vel(v), m_fBackjump(backjump) {}

Crosser::Crosser(PlayState* g, Texture* t, std::istream& is, float backjump)
    : SceneObject(g,t,is), m_fBackjump(backjump)
{
    float vX;
    is >> vX;
    m_Vel.setX(vX);
}

void Crosser::update()
{
    m_Pos = m_Pos + m_Vel * SDLApplication::DELTA;

    if (m_Pos.getX() < -PlayState::BAST)
        m_Pos.setX(m_Pos.getX() + m_fBackjump);
    else if (m_Pos.getX() > SDLApplication::WINDOW_WIDTH + PlayState::BAST)
        m_Pos.setX(m_Pos.getX() - m_fBackjump);
}
