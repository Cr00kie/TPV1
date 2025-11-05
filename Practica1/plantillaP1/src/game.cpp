#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

#include <fstream>
#include <limits>

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
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
  : exit(false), rndGenerator(time(0)), timeNextWasp(0), nFreeNests(NUM_NIDOS)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

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

	

	// Crea las ranas en los nidos
	for (int i = 0; i < NUM_NIDOS; ++i) {
        HomedFrog* pF = new HomedFrog(this, textures[TextureName::FROG], Vector2D<float>(PRIMER_NIDO_X + i * DIST_NIDOS, PRIMER_NIDO_Y), i);
        nidos[i] = false;
        gameObjects.push_back(pF);
	}

	infoBar = new InfoBar(this, textures[FROG], Vector2D(HUD_POS_X, HUD_POS_Y));

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{

    for (SceneObject* go : gameObjects) delete go;

	delete infoBar;

	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[BACKGROUND]->render();

    for (SceneObject* go : gameObjects) go->render();
    
	infoBar->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	//Crea la avispa
	if (timeNextWasp <= 0)
	{
        Wasp* wasp = new Wasp(this, textures[WASP],
            Vector2D<float>(PRIMER_NIDO_X + getRandomHomeIndex() * DIST_NIDOS, PRIMER_NIDO_Y),
            Vector2D<float>(0, 0),
            float(getRandomRange(MIN_WASP_ALIVE, MAX_WASP_ALIVE)));
        gameObjects.push_back(wasp);
        wasp->SetAnchor(--gameObjects.end());

		timeNextWasp = (float)getRandomRange(MAX_WASP_ALIVE+MIN_WASP_DEAD, MAX_WASP_ALIVE+MAX_WASP_DEAD);
	}
	timeNextWasp -= DELTA;

    for (SceneObject* go : gameObjects) {
        go->update();
    }

    for (int i = 0; i < objectsToDelete.size(); ++i) {
        delete (*objectsToDelete[i]);
        gameObjects.erase(objectsToDelete[i]);
    }
    objectsToDelete.clear();

    infoBar->updateVidas(frog->getFrogHealth());

	checkVictory();
}

void
Game::run()
{
    // Carga los datos del archivo
    loadMap();

	while (!exit) {
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

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_0) {
            const SDL_MessageBoxButtonData buttons[] = {
                {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel"},
                {0, 1, "Accept"},
            };
            SDL_MessageBoxData boxData = {
                SDL_MESSAGEBOX_INFORMATION,
                window,
                "Restarting game",
                "Are you sure you want to restart the game?",
                2,
                buttons
            };
            int button;
            SDL_ShowMessageBox(&boxData, &button);
            if (button == 1) {
                restartGame();
            }
        }

        frog->handleEvent(event);
	}
}

// Devuelve el indice a un nido vacio aleatorio
int Game::getRandomHomeIndex()
{
	// No hay nidos libres
	if (nFreeNests == 0) return -1;

	// Escogemos un nido libre aleatorio
	int nNidoSeleccionado = getRandomRange(1, nFreeNests);

	// Buscamos que indice es ese nido libre escogido
	int nNidosLibres = 0;
	int i = 0;
	while (nNidosLibres != nNidoSeleccionado) {
        if (!nidos[i]) ++nNidosLibres;
		++i;
	}
	return i-1; // Corregimos el ++i del bucle
}

void Game::checkVictory()
{
	if (nFreeNests <= 0) endGame(false);
}

void Game::occupyNest(int index)
{
    nidos[index] = true;
    nFreeNests--;
}

void Game::deleteAfter(Anchor object)
{
    objectsToDelete.push_back(object);
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision colData;

    for (SceneObject* go : gameObjects) {
        colData = go->checkCollision(rect);
        if (colData.type != colData.NONE) return colData;
    }

	return colData;
}

void Game::loadMap()
{
	std::ifstream file(MAP_FILE);
	if (!file.is_open()) throw FileNotFoundError(MAP_FILE);
	else {
		char id;
		int l = 1;
		file.get(id);
		while(!file.fail())
		{
			switch (id) {
			case 'F':
                frog = new Frog(this, textures[FROG], file);
				gameObjects.push_back(frog);
				break;
			case 'V':
				gameObjects.push_back(new Vehicle(this, textures[CAR1], file));
				break;
			case 'L':
                gameObjects.push_back(new Log(this, textures[LOG1], file));
				break;
			case 'T':
                gameObjects.push_back(new TurtleGroup(this, textures[TURTLE], file));
                break;
			case '#':
				break;
			default:
                throw FileFormatError(MAP_FILE, l);
			}
			if (file.fail()) throw FileFormatError(MAP_FILE, l);
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			file.get(id);
			l++;
		}
	}
}

int Game::getRandomRange(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(rndGenerator);
}

void Game::endGame(bool hasLost)
{
	if (hasLost) std::cout << "Has perdido ...\n";
	else std::cout << "Has ganado!\n";
	exit = true;
}

void Game::restartGame() {
    for (SceneObject* go : gameObjects) delete go;
    delete infoBar;

    gameObjects.clear();

    for (int i = 0; i < NUM_NIDOS; ++i) {
        HomedFrog* pF = new HomedFrog(this, textures[TextureName::FROG], Vector2D<float>(PRIMER_NIDO_X + i * DIST_NIDOS, PRIMER_NIDO_Y), i);
        nidos[i] = false;
        gameObjects.push_back(pF);
    }

    infoBar = new InfoBar(this, textures[FROG], Vector2D(HUD_POS_X, HUD_POS_Y));
    loadMap();
}
