// Adrian Isasi Martinez
// Grupo: G31

//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

// TODO
// - [x] Cambiar a la jerarquía de excepciones
// - [ ] Preguntarle a Ruben que hago con los memory leaks que salen al lanzar una excepcion (Se lanzan en el constructor de game) (Por ahora he puesto loadmap en run())
// - [ ] Preguntarle a Ruben como hacemos que se muestre la caja de mensaje en main si no tenemos el *window


#include "game.h"
#include "GameError.h"

int main(int argc, char* argv[])
{
	try {
		Game().run();
	}
	catch (GameError e) {
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error de juego", e.c_str());
        std::cout << e.what() << '\n';
	}

	return 0;
}
