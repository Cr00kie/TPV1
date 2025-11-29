#include "PlayState.h"
#include <fstream>

#include "FileNotFoundError.h"
#include "FileFormatError.h"

#include "PauseState.h"
#include "EndState.h"

#include "Vehicle.h"
#include "Log.h"
#include "Turtle.h"
#include "Frog.h"
#include "HomedFrog.h"
#include "Label.h"
#include "vector2D.h"
#include "InfoBar.h"
#include "Wasp.h"

int PlayState::getRandomHomeIndex()
{
    // No hay nidos libres
    if (nFreeNests == 0) return -1;

    // Escogemos un nido libre aleatorio
    int nNidoSeleccionado = getRandomRange(1, nFreeNests);

    // Buscamos que indice es ese nido libre escogido
    int nNidosLibres = 0;
    int i = 0;
    while (nNidosLibres != nNidoSeleccionado)
    {
        if (!nidos[i]) ++nNidosLibres;
        ++i;
    }
    return i - 1; // Corregimos el ++i del bucle
}

void PlayState::checkVictory()
{
    if (nFreeNests <= 0) endGame(false);
}

PlayState::PlayState(SDLApplication* game, const std::string& mapName)
    : GameState(game),
    rndGenerator(time(0)),
    nFreeNests(NUM_NIDOS),
    timeNextWasp(0),
    currentMap(mapName)
{
    try
    {
        GameState::addObject(new Label(this, m_pGame->getTexture(SDLApplication::GAME_BACKGROUND), { 0,0 }));

        for (int i = 0; i < NUM_NIDOS; ++i)
        {
            HomedFrog* pF = new HomedFrog(this, m_pGame->getTexture(SDLApplication::FROG), Vector2D<float>(PRIMER_NIDO_X + i * DIST_NIDOS, PRIMER_NIDO_Y), i);
            nidos[i] = false;
            GameState::addObject(pF);
            PlayState::addObject(pF);
        }

        infoBar = new InfoBar(this, m_pGame->getTexture(SDLApplication::FROG), Vector2D(HUD_POS_X, HUD_POS_Y));
        GameState::addObject(infoBar);

        loadMap(currentMap);
    }
    catch (GameError& e)
    {
        throw e;
    }
}

Collision PlayState::checkCollision(const SDL_FRect& rect) const
{
    Collision colData;

    for (SceneObject* go : sceneObjects)
    {
        colData = go->checkCollision(rect);
        if (colData.type != colData.NONE) return colData;
    }

    return colData;
}

void PlayState::loadMap(const std::string& mapName)
{
    std::string filePath = "../assets/maps/" + mapName + ".txt";
    std::ifstream file(filePath);
    if (!file.is_open()) throw FileNotFoundError(filePath);
    else
    {
        char id;
        int l = 1;
        file.get(id);
        while (!file.fail())
        {
            switch (id)
            {
            case 'F':
                CreateFrog(file);
                break;
            case 'V':
                CreateVehicle(file);
                break;
            case 'L':
                CreateLog(file);
                break;
            case 'T':
                CreateTurtleGroup(file);
                break;
            case 'W':
                CreateWasp(file);
            case '#':
                break;
            default:
                throw FileFormatError(filePath, l);
            }
            if (file.fail()) throw FileFormatError(filePath, l);
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file.get(id);
            l++;
        }
    }
}

void PlayState::CreateWasp(std::ifstream& file)
{
    Wasp* wasp = new Wasp(this, m_pGame->getTexture(SDLApplication::WASP), file);
    wasp->SetPlayStateAnchor(PlayState::addObject(wasp));
    wasp->SetGameStateAnchor(GameState::addObject(wasp));
}

void PlayState::CreateTurtleGroup(std::ifstream& file)
{
    TurtleGroup* turtles = new TurtleGroup(this, m_pGame->getTexture(SDLApplication::TURTLE), file);
    PlayState::addObject(turtles);
    GameState::addObject(turtles);
}

void PlayState::CreateLog(std::ifstream& file)
{
    Log* log = new Log(this, m_pGame->getTexture(SDLApplication::LOG1), file);
    PlayState::addObject(log);
    GameState::addObject(log);
}

void PlayState::CreateVehicle(std::ifstream& file)
{
    Vehicle* vehicle = new Vehicle(this, m_pGame->getTexture(SDLApplication::CAR1), file);
    PlayState::addObject(vehicle);
    GameState::addObject(vehicle);
}

void PlayState::CreateFrog(std::ifstream& file)
{
    frog = new Frog(this, m_pGame->getTexture(SDLApplication::FROG), file);
    PlayState::addObject(frog);
    GameState::addObject(frog);
    addEventListener(frog);
}

int PlayState::getRandomRange(int min, int max)
{
    return std::uniform_int_distribution<int>(min, max)(rndGenerator);
}

void PlayState::endGame(bool hasLost)
{
    m_pGame->replaceState(new EndState(m_pGame, !hasLost));
}

void PlayState::occupyNest(int index)
{
    nidos[index] = true;
    nFreeNests--;
}

PlayState::Anchor PlayState::addObject(SceneObject* so)
{
    sceneObjects.push_front(so);
    return sceneObjects.begin();
}

void PlayState::removeObject(PlayState::Anchor it)
{
    sceneObjects.erase(it);
}

void PlayState::update()
{
    //Crea la avispa
    CreateRandomWasp();

    UpdateHUD();

    GameState::update();

    checkVictory();
}

void PlayState::UpdateHUD()
{
    infoBar->updateVidas(frog->getFrogHealth());
    infoBar->updateTimer(frog->getFrogLiveTime());
}

void PlayState::handleEvent(const SDL_Event& e)
{
    GameState::handleEvent(e);
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
        if (e.key.key == SDLK_ESCAPE) m_pGame->pushState(new PauseState(m_pGame, this));
    }
}

void PlayState::CreateRandomWasp()
{
    if (timeNextWasp <= 0)
    {
        Wasp* wasp = new Wasp(this, m_pGame->getTexture(SDLApplication::WASP),
            Vector2D<float>(PRIMER_NIDO_X + getRandomHomeIndex() * DIST_NIDOS, PRIMER_NIDO_Y),
            Vector2D<float>(0, 0),
            float(getRandomRange(MIN_WASP_ALIVE, MAX_WASP_ALIVE)));
        wasp->SetPlayStateAnchor(PlayState::addObject(wasp));
        wasp->SetGameStateAnchor(GameState::addObject(wasp));

        timeNextWasp = (float)getRandomRange(MAX_WASP_ALIVE + MIN_WASP_DEAD, MAX_WASP_ALIVE + MAX_WASP_DEAD);
    }
    timeNextWasp -= SDLApplication::DELTA;
}

const std::string& PlayState::getMapName() const
{
    return currentMap;
}
