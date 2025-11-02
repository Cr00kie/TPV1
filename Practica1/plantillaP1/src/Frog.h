#pragma once
#include "texture.h"
#include "vector2D.h"
#include "SceneObject.h"
#include "Collision.h"

class Game;
struct Collision;

class Frog : public SceneObject{
private:
	static constexpr int STEP = 32;
	static constexpr float ANIM_DURATION = 0.08f;
	static constexpr int DEFAULT_MAX_HEALTH = 3;
	static constexpr int COLLIDER_REDUCTION = 15;
	Vector2D<float> m_StartPos;
	Vector2D<float> m_Vel;
	Vector2D<float> m_LastDir;
	int m_nHealth;
	bool m_bMove;
	float m_fAnimTime;

public:
	Frog(Game* game, Texture* texture, const Vector2D<float>& pos, int maxHealth = DEFAULT_MAX_HEALTH);
	Frog(Game* game, Texture* texture, std::istream& is, int maxHealth = DEFAULT_MAX_HEALTH);
	void render() const;
	void update();
	void handleEvent(const SDL_Event&) override;
    void checkCollisions();
    Collision checkCollision(SDL_FRect other) override { return Collision(); }

	int getFrogHealth() const;

private:
	void die();
	void resetPos();
};
