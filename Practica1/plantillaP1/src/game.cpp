#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

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
  : exit(false), rndGenerator(time(0)), homedFrogs(NUM_NIDOS), timeNextWasp(0), nFreeNests(5)
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

	// Carga los datos del archivo
	loadMap();

	// Crea las ranas en los nidos
	for (int i = 0; i < NUM_NIDOS; ++i) {
		homedFrogs[i] = new HomedFrog(this, textures[FROG], Vector2D<float>(PRIMER_NIDO_X + i * DIST_NIDOS, PRIMER_NIDO_Y));
	}

	infoBar = new InfoBar(this, textures[FROG], Vector2D(HUD_POS_X, HUD_POS_Y));

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{

	delete frog;

	for (Vehicle* v : vehicles) delete v;
	for (Log* l : logs) delete l;
	for (HomedFrog* f : homedFrogs) delete f;
	for (Wasp* w : wasps) delete w;
	for (Turtle* t : turtles) delete t;

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

	for (Vehicle* v : vehicles) v->render();
	for (Log* l : logs) l->render();
	for (HomedFrog* f : homedFrogs) f->render();
	for (Wasp* w : wasps) w->render();
	for (Turtle* t : turtles) t->render();

	frog->render();

	infoBar->render(frog->getFrogHealth());

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	//Crea la avispa
	if (timeNextWasp <= 0)
	{
		wasps.push_back(new Wasp(this, textures[WASP],
			Vector2D<float>(PRIMER_NIDO_X + getRandomHomeIndex() * DIST_NIDOS, PRIMER_NIDO_Y),
			Vector2D<float>(0, 0),
			float(getRandomRange(MIN_WASP_ALIVE, MAX_WASP_ALIVE))));
		timeNextWasp = (float)getRandomRange(MAX_WASP_ALIVE+MIN_WASP_DEAD, MAX_WASP_ALIVE+MAX_WASP_DEAD);
	}
	timeNextWasp -= DELTA;

	// Actualizar objetos
	frog->update();

	for (Vehicle* v : vehicles) v->update();
	for (Log* l : logs) l->update();
	for (Turtle* t : turtles) t->update();
	for (int i = 0; i < wasps.size(); ) {
		wasps[i]->update();
		if (!wasps[i]->isAlive())
		{
			delete wasps[i];
			wasps.erase(wasps.begin() + i);
		}
		else {
			++i;
		}
	}

    frog->checkCollisions();

	checkVictory();
}

void
Game::run()
{
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
		if (!homedFrogs[i]->IsActive()) ++nNidosLibres;
		++i;
	}
	return i-1; // Corregimos el ++i del bucle
}

void Game::checkVictory()
{
	if (nFreeNests <= 0) endGame(false);
}

void Game::occupyNest()
{
    nFreeNests--;
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision colData;

	for (Vehicle* v : vehicles) 
	{
		colData = v->checkCollision(rect);
		if (colData.type != colData.NONE) return colData;
	}

	for(Wasp* w : wasps)
	{
		colData = w->checkCollision(rect);
		if (colData.type != colData.NONE) return colData;
	}

	for (HomedFrog* f : homedFrogs)
	{
		colData = f->checkCollision(rect);
		if (colData.type != colData.NONE) return colData;
	}

	for (Log* l : logs)
	{
		colData = l->checkCollision(rect);
		if (colData.type != colData.NONE) return colData;
	}

	for (Turtle* t : turtles)
	{
		colData = t->checkCollision(rect);
		if (colData.type != colData.NONE) return colData;
	}


	return colData;
}

void Game::loadMap()
{
	std::ifstream file(MAP_FILE);
	if (!file.is_open()) throw "Error: No se encuentra el mapa: "s + MAP_FILE;
	else {
		char id;
		int l = 1;
		file.get(id);
		while(!file.fail())
		{
			switch (id) {
			case 'F':
				frog = new Frog(this, textures[FROG], file);
				break;
			case 'V':
				vehicles.push_back(new Vehicle(this, textures[CAR1], file));
				break;
			case 'L':
				logs.push_back(new Log(this, textures[LOG1], file));
				break;
			case 'T':
				turtles.push_back(new Turtle(this, textures[TURTLE], file));
			case '#':
				break;
			default:
				throw "Error: Identificador de objeto invalido '"s + id + "' en la linea "s + std::to_string(l);
			}
			if (file.fail()) throw "Error: no se ha podido leer el objeto '"s + id + "' en la linea "s + std::to_string(l);
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
