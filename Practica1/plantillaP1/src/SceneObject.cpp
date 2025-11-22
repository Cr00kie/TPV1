#include "SceneObject.h"
#include "GameObject.h"
#include "GameState.h"
#include "PlayState.h"
#

SceneObject::SceneObject(GameState* g, Texture* t, Vector2D<float> p, float w, float h) : GameObject(g), m_pTexture(t), m_Pos(p) {
    m_nWidth = w == -1 ? m_pTexture->getFrameWidth() : w;
    m_nHeight = h == -1 ? m_pTexture->getFrameHeight() : h;
    m_pPlayState = static_cast<PlayState*>(g);
}

SceneObject::SceneObject(GameState* g, Texture* t, std::istream& is, float w, float h) : GameObject(g), m_pTexture(t)
{
    m_nWidth = w == -1 ? m_pTexture->getFrameWidth() : w;
    m_nHeight = h == -1 ? m_pTexture->getFrameHeight() : h;

    float x, y;
    is >> x >> y;
    m_Pos.setX(x);
    m_Pos.setY(y);
    m_pPlayState = static_cast<PlayState*>(g);
}

SDL_FRect SceneObject::getBoundingBox() const { return SDL_FRect(m_Pos.getX(), m_Pos.getY(), m_nWidth, m_nHeight); }

void SceneObject::render() const { m_pTexture->render(getBoundingBox()); }
