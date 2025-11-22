#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <random>

class SceneObject;
class InfoBar;
class Frog;
struct Collision;

class PlayState : public GameState
{
public:
    using Anchor = std::list<SceneObject*>::iterator;
    
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
    static constexpr int MIN_WASP_ALIVE = 4;
    static constexpr int MAX_WASP_ALIVE = 7;
    // Tiempo sin avispa en pantalla
    static constexpr int MIN_WASP_DEAD = 5;
    static constexpr int MAX_WASP_DEAD = 8;
    // Bastidores
    static constexpr int BAST = 150;

private:
    std::mt19937_64 rndGenerator;

    int getRandomHomeIndex();
    void checkVictory();

    // Elemento del juego
    // TODO: añadir atributos para los objetos del juego
    std::list<SceneObject*> sceneObjects;
    Frog* frog;
    bool nidos[NUM_NIDOS];
    int nFreeNests;
    float timeNextWasp;
    std::vector<Anchor> objectsToDelete;
    std::string currentMap;

    InfoBar* infoBar;

    void restartGame();

    void freeMemory();

public:
    PlayState(SDLApplication*, const std::string&);
    ~PlayState();

    // Comprueba si hay algún objeto colocado en ese rectángulo
    Collision checkCollision(const SDL_FRect& rect) const;

    void loadMap(std::string&);

    void CreateWasp(std::ifstream& file);

    void CreateTurtleGroup(std::ifstream& file);

    void CreateLog(std::ifstream& file);

    void CreateVehicle(std::ifstream& file);

    void CreateFrog(std::ifstream& file);

    int getRandomRange(int min, int max);

    void endGame(bool hasLost);

    // Para que la homedFrog actualiza los nFreeNests
    void occupyNest(int index);

    PlayState::Anchor addObject(SceneObject*);
    void removeObject(PlayState::Anchor);

    void update() override;
    void handleEvent(const SDL_Event&) override;
    void CreateRandomWasp();
};
