#include "Crosser.h"
#include "game.h"

Crosser::Crosser(Game* g, Texture* t, Vector2D<float> p, Vector2D<float> v, float backjump) : SceneObject(g, t, p), m_Vel(v), m_fBackjump(backjump) {}

Crosser::Crosser(Game* g, Texture* t, std::istream& is, float backjump)
    : SceneObject(g,t,is), m_fBackjump(backjump)
{
    float vX;
    is >> vX;
    m_Vel.setX(vX);
}

void Crosser::update()
{
    m_Pos = m_Pos + m_Vel * Game::DELTA;

    if (m_Pos.getX() < -Game::BAST)
        m_Pos.setX(m_Pos.getX() + m_fBackjump);
    else if (m_Pos.getX() > Game::WINDOW_WIDTH + Game::BAST)
        m_Pos.setX(m_Pos.getX() - m_fBackjump);
}
