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
    int m_nIndex;

public:
	HomedFrog(Game* game, Texture* texture, const Vector2D<float>& pos, int index);
	void render() const override;
    // No lo hago const porque debe ser capaz de activarse si colisiona con la rana
    Collision checkCollision(SDL_FRect) override;
	void update() override;
	bool IsActive() const;

private:
	void SetActive();
};
