// Adrian Isasi Martinez
// Grupo: G31

//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

// TODO
// - [x] cambiar a Game::CONSTANTE
// - [x] checkCollisions en la rana
// - [x] nNidosAlive variable de game
// - [x] Set is active de homedFrog en la propia homedFrog
// - [x] Contar tiempo de update y hacer bien el SDL_DELAY


#include "game.h"

int main(int argc, char* argv[])
{
	try {
		Game().run();
	}
	catch (std::string e) {
		std::cout << e;
	}

	return 0;
}
