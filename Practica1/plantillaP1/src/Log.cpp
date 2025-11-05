#include "Log.h"
#include "Collision.h"
#include <string>
using namespace std::string_literals;

Log::Log(Game* game, Texture* texture, const Vector2D<float>& pos, const Vector2D<float>& vel)
	: Platform(game, texture, pos, vel, Game::BAST*2+Game::WINDOW_WIDTH)
{
}

Log::Log(Game* game, Texture* texture, std::istream& is)
	: Platform(game, texture, is, Game::BAST*2 + Game::WINDOW_WIDTH)
{
	int type;
	is >> type;

	if (type < 0 || type > 1) throw "Error: no se ha podido leer log"s;

	m_pTexture = game->getTexture(Game::TextureName(Game::LOG1 + type));

    m_nWidth = m_pTexture->getFrameWidth();
    m_nHeight = m_pTexture->getFrameHeight();
}
