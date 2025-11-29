#include "SDLApplication.h"

#include <string>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include <limits>
#include <memory>

#include "texture.h"
#include "SDLError.h"
#include "MainMenuState.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, SDLApplication::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},

	{"background.png"},
    {"menuBackground.png"},

	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"turtle.png", 1, 7},
	{"wasp.png"},

    {"./texts/Avispado.png"},
    {"./texts/CONTINUAR.png"},
    {"./texts/ELIGE UN MAPA.png"},
    {"./texts/GAME OVER.png"},
    {"./texts/HAS GANADO.png"},
    {"./texts/left.png"},
    {"./texts/right.png"},
    {"./texts/Original.png"},
    {"./texts/Práctica 1.png"},
    {"./texts/REINICIAR.png"},
    {"./texts/SALIR.png"},
    {"./texts/Trivial.png"},
    {"./texts/Veloz.png"},
    {"./texts/VOLVER AL MENÚ.png"},
};

SDLApplication::SDLApplication() :
    m_bExit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        throw SDLError();
    }

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

    textures.fill(nullptr);

    try {
        soundManager.load();

        if (window == nullptr)
            throw SDLError();

        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer == nullptr)
            throw SDLError();

        // Carga las texturas al inicio
        for (size_t i = 0; i < textures.size(); i++) {
            auto [name, nrows, ncols] = textureList[i];
            textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    catch (GameError& e) {
        freeMemory();
        throw e;
    }
}

SDLApplication::~SDLApplication()
{
    freeMemory();
}

void SDLApplication::freeMemory()
{
    soundManager.unload();

    for (Texture* t : textures) delete t;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void
SDLApplication::run()
{
    pushState(new MainMenuState(this));

	while (!m_bExit && !empty()) {
        Uint64 frameStart = SDL_GetTicks();
		handleEvents();
		update();
        render();
        Uint64 delta = SDL_GetTicks() - frameStart;

        if(delta < DELTA_MS)
        {
            SDL_Delay((int)(DELTA_MS-delta));
        }
	}
}

void SDLApplication::render()
{
    SDL_RenderClear(renderer);
    GameStateMachine::render();
    SDL_RenderPresent(renderer);
}

void
SDLApplication::handleEvents()
{
    SDL_Event event;

    // Only quit is handled directly, everything else is delegated
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            m_bExit = true;

        handleEvent(event);
    }

}

