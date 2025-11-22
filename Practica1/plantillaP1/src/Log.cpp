#include "Log.h"
#include "Collision.h"
#include <string>
#include "FileFormatError.h"
#include "PlayState.h"
#include "SDLApplication.h"

using namespace std::string_literals;

Log::Log(GameState* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Platform(game, texture, pos, vel, PlayState::BAST*2+SDLApplication::WINDOW_WIDTH)
{
}

Log::Log(GameState* game, Texture* texture, std::istream& is)
	: Platform(game, texture, is, PlayState::BAST*2 + SDLApplication::WINDOW_WIDTH)
{
	int type;
	is >> type;

	//if (type < 0 || type > 1) throw "Error: no se ha podido leer log"s;

	m_pTexture = game->getSDLApplication()->getTexture(SDLApplication::TextureName(SDLApplication::LOG1 + type));

    m_nWidth = m_pTexture->getFrameWidth();
    m_nHeight = m_pTexture->getFrameHeight();
}
