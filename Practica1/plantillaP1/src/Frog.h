#pragma once
#include "texture.h"
#include "vector2D.h"
#include "SceneObject.h"
#include "Collision.h"
#include "EventHandler.h"

class SDLApplication;
struct Collision;

class Frog : public SceneObject, public EventHandler{
public:
	static constexpr int STEP = 32;
	static constexpr float ANIM_DURATION = 0.1f;
	static constexpr int DEFAULT_MAX_HEALTH = 3;
	static constexpr int COLLIDER_REDUCTION = 5;
    // Tiempo partida
    static constexpr float TIMER = 30;
private:
	Vector2D<float> m_StartPos;
	Vector2D<float> m_Vel;
	Vector2D<float> m_LastDir;
	int m_nHealth;
	bool m_bMove;
	float m_fAnimTime;
    float m_fLiveTime;

public:
	Frog(GameState* game, Texture* texture, const Vector2D<float>& pos, int maxHealth = DEFAULT_MAX_HEALTH);
	Frog(GameState* game, Texture* texture, std::istream& is, int maxHealth = DEFAULT_MAX_HEALTH);
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&);
    void checkCollisions();
    Collision checkCollision(SDL_FRect other) override { return Collision(); }

	int getFrogHealth() const;
    float getFrogLiveTime() const;

private:
	void die();
	void resetFrog();
protected:
    virtual SDL_FRect getBoundingBox() const override;
};
