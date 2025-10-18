#pragma once
#include "game.h"
#include "texture.h"
#include "Vector2D.h"

class Game;


class Frog {
private:
	static constexpr int STEP = 32;
	static constexpr float ANIM_DURATION = 0.08;
	static constexpr int DEFAULT_MAX_HEALTH = 3;
	static constexpr int COLLIDER_REDUCTION = 10;
	Game* m_pGame;
	Texture* m_pTexture;
	Vector2D<float> m_Pos;
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
	void handleEvent(const SDL_Event&);

	const SDL_FRect getCollider() const;
	const Vector2D<float>& getFrogPos() const;
	int getFrogHealth() const;
	void setVelocity(Vector2D<float> vel);
	void die();
	void resetPos();
};
