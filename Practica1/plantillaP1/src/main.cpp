// Adrian Isasi Martinez
// Grupo: G31

//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

// TODO
// - [x] La avispa debe desaparecer un tiempo aleatorio
// - [x] Alocar las avispas en heap y destruirlas para practicar
// - [x] La avispa no puede aparecer sobre una HomedFrog
// - [x] Hacer que el juego termine cuando ocupas todos los nidos
// - [x] Mostrar mensaje de victoria o derrota cuando ganas o pierdes
// - [x] Hacer tareas opcionales
// - [x] Arreglar los clamps usando STEP y WINDOW_WIDTH
// - [x] Quitar numeros magicos
// - [x] Cambiar struct de collision para incluir la collision con HomedFrog como tipo distinto
// - [ ] Revisar reglas de entrega y enunciado


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
