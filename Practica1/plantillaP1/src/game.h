#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <vector>
#include <random>

#include "Frog.h"
#include "HomedFrog.h"
#include "Log.h"
#include "Vehicle.h"
#include "Wasp.h"
#include "Collision.h"
#include "InfoBar.h"
#include "Turtle.h"

// Declaraciones anticipadas
class Texture;
class Frog;
class HomedFrog;
class Log;
class Vehicle;
class Wasp;
class InfoBar;
class Turtle;
struct Collision;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	static constexpr float DELTA = 1.f/FRAME_RATE;
	static constexpr float DELTA_MS = 1000.f/FRAME_RATE;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 210;
	// Posicion HUD
	static constexpr int HUD_POS_Y = 435;
	static constexpr int HUD_POS_X = 0;
	// Numero de nidos en el mapa
	static constexpr int NUM_NIDOS = 5;
	// Distancia en px entre los nidos del mapa
	static constexpr float DIST_NIDOS = 96.f;
	// Posicion del primer nido
	static constexpr float PRIMER_NIDO_X = 14.f;
	static constexpr float PRIMER_NIDO_Y = 21.f;
	// Tiempo de vida de avispa
	static constexpr int MIN_WASP_ALIVE = 5;
	static constexpr int MAX_WASP_ALIVE = 10;
	// Tiempo sin avispa en pantalla
	static constexpr int MIN_WASP_DEAD = 5;
	static constexpr int MAX_WASP_DEAD = 10;
	// Bastidores
	static constexpr int BAST_IZQ = -150;
	static constexpr int BAST_DER = 150;

	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		LOG1,
		LOG2,
		TURTLE,
		WASP,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	std::mt19937_64 rndGenerator;

	void render() const;
	void update();
	void handleEvents();
	int getRandomHomeIndex();
	void checkVictory();
    

	int exit;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego
	Frog* frog;
	HomedFrog *homedFrog;
	std::vector<Vehicle*> vehicles;
	std::vector<Log*> logs;
	std::vector<HomedFrog*> homedFrogs;
    int nFreeNests;
	std::vector<Wasp*> wasps;
	std::vector<Turtle*> turtles;
	float timeNextWasp;

	InfoBar* infoBar;

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision
checkCollision(const SDL_FRect& rect) const;

	void loadMap();

	int getRandomRange(int min, int max);

	void endGame(bool hasLost);
    // Para que la homedFrog actualiza los nFreeNests
    void occupyNest();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
