#include "Button.h"
#include "GameState.h"
#include "SDL3/SDL.h"

void Button::handleEvent(const SDL_Event& event)
{
    if(m_bIsActive)
    {
        if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
            SDL_FPoint mousePos = { event.button.x, event.button.y };
            SDL_FRect hitDetectionRectangle(m_Pos.getX(), m_Pos.getY(), m_pTexture->getFrameWidth(), m_pTexture->getFrameHeight());
            m_bHovered = SDL_PointInRectFloat(&mousePos, &hitDetectionRectangle);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && m_bHovered)
        {
            m_onClick();
        }
    }
}

void Button::setActive(bool active)
{
    m_bIsActive = active;
}

Button::Button(GameState* g, Texture* t, Vector2D<float> p, SDL_Color baseColor, SDL_Color hoveredColor)
    : Label(g, t, p, baseColor),
    m_bHovered(false), m_bIsActive(true), m_hoveredColor(hoveredColor)
{
    m_pGame->addEventListener(this);
}

void Button::render() const
{
    if (m_bIsActive)
    {
        SDL_FRect target(m_Pos.getX(), m_Pos.getY(), m_pTexture->getFrameWidth(), m_pTexture->getFrameHeight());
        if (m_bHovered)
            m_pTexture->render(target, m_hoveredColor);
        else m_pTexture->render(target, m_baseColor);
    }
}

void Button::connect(Callback callbackToWire)
{
    m_onClick = callbackToWire;
}
