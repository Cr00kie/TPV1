#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "SceneObject.h"

class Game;
struct Collision;

class HomedFrog : public SceneObject{
private:
	bool m_bIsActive;

public:
	HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos);
	void render() const;
    // No lo hago const porque debe ser capaz de activarse si colisiona con la rana
    Collision checkCollision(SDL_FRect) override;
	void update();
	bool IsActive() const;
	void SetActive();
};
