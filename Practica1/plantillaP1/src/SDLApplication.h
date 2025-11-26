#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <list>
#include <vector>
#include <random>
#include "gameStateMachine.h"
#include "texture.h"

/**
 * Clase principal del juego.
 */
class SDLApplication : public GameStateMachine
{
public:
    // Se actualiza el juego cada tantos milisegundos
    static constexpr int FRAME_RATE = 30;
    static constexpr float DELTA = 1.f / FRAME_RATE;
    static constexpr float DELTA_MS = 1000.f / FRAME_RATE;

    // Tamaño real de la ventana
    static constexpr int WINDOW_WIDTH = 448;
    static constexpr int WINDOW_HEIGHT = 484;

	enum TextureName
	{
        // Player
		FROG = 0,

        // BG
		GAME_BACKGROUND,
        MENU_BACKGROUND,

        // Obstacles
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		LOG1,
		LOG2,
		TURTLE,
		WASP,

        // UI
        AVISPADO,
        CONTINUAR,
        ELIGE_UN_MAPA,
        GAME_OVER,
        HAS_GANADO,
        LEFT, // Used also for right
        RIGHT,
        ORIGINAL,
        PRACTICA_1,
        REINICIAR,
        SALIR,
        TRIVIAL,
        VELOZ,
        VOLVER_AL_MENU,


		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;
    bool m_bExit;
    void handleEvents();

public:
	SDLApplication();
	~SDLApplication();

	void freeMemory();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;

	// Ejecuta el bucle principal del juego
	void run();
    void render();
};

inline Texture*
SDLApplication::getTexture(TextureName name) const
{
	return textures[name];
}

inline SDL_Renderer* SDLApplication::getRenderer() const
{
    return renderer;
}

inline SDL_Window* SDLApplication::getWindow() const
{
    return window;
}

#endif // GAME_H
