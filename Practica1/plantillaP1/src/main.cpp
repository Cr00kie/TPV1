// Adrian Isasi Martinez
// Grupo: G31

//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

// TODO
// - [ ] 


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
