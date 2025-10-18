#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Frog.h"
#include "Vehicle.h"
#include "Log.h"
#include "Wasp.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* imgBase = "./assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"goal.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},
};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	frog = new Frog(this, textures[FROG], Vector2D<float>(224, 440));
	v1 = new Vehicle(this, textures[CAR1], Vector2D<float>(598, 240), Vector2D<float>(-5, 0));
	v2 = new Vehicle(this, textures[CAR2], Vector2D<float>(598, 260), Vector2D<float>(-5, 0));
	l1 = new Log(this, textures[LOG1], Vector2D<float>(598, 200), Vector2D<float>(-0.5, 0));

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	// TODO: liberar memoria reservada por la clase
	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}

	delete frog;
	delete v1;
	delete v2;
	delete l1;

}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[BACKGROUND]->render();
	frog->render();
	v1->render();
	v2->render();
	l1->render();

	// TODO

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// TODO
	frog->update();
	v1->update();
	v2->update();
	l1->update();

}

void
Game::run()
{
	while (!exit) {
		handleEvents();
		render();
		update();
		SDL_Delay(16);
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;
		frog->handleEvent(event);
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO:
	return false;
}
