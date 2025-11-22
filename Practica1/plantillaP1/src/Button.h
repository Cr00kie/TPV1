#pragma once
#include "Label.h"
#include "EventHandler.h"
#include <functional>

class Button :
    public Label, public EventHandler
{
    using Callback = std::function<void()>;

    Callback m_onClick;
    bool m_bHovered;
    bool m_bIsActive;
    SDL_Color m_hoveredColor = { 255, 255, 0};
    SDL_Color m_baseColor;


public:
    Button(GameState*, Texture*, Vector2D<float>, SDL_Color baseColor = { 255,255,255 }, SDL_Color hoveredColor = { 255, 255, 0 });
    ~Button() = default;
    void render() const override;
    void connect(Callback callbackToWire);
    void handleEvent(const SDL_Event&) override;
    void setActive(bool active);
};

