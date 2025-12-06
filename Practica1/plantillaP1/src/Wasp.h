#pragma once
#include "texture.h"
#include "vector2D.h"
#include "SceneObject.h"
#include "PlayState.h"


class SDLApplication;
struct Collision;

class Wasp : public SceneObject{
private:
	Vector2D<float> m_Vel;
	float m_fTiempoVida;
    GameState::Anchor m_GameStateAnchor;
    PlayState::Anchor m_PlayStateAnchor;

public:
	Wasp(PlayState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel, float tiempoVida);
    Wasp(PlayState* game, Texture* texture, std::istream& is);
	void update() override;
    void render() const override;
	Collision checkCollision(SDL_FRect) override;
	bool isAlive() const;
    void SetPlayStateAnchor(PlayState::Anchor anchor);
    void SetGameStateAnchor(GameState::Anchor anchor);
};
