#include "Label.h"
#include "SDLApplication.h"
#include "SDL3/SDL.h"

Label::Label(GameState* game, Texture* texture, Vector2D<float> pos, SDL_Color textColor)
    : GameObject(game), m_pTexture(texture), m_Pos(pos), m_textColor(textColor)
{

}

void Label::render() const
{
    SDL_FRect target(m_Pos.getX(), m_Pos.getY(), m_pTexture->getFrameWidth(), m_pTexture->getFrameHeight());
    m_pTexture->render(target, m_textColor);
}

void Label::update()
{
}
