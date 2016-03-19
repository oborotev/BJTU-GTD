//
// Created by storm on 19/03/16.
//

# include "tilesetHandler.h"

const int       TilesetHandler::init(const sf::Texture &tileset)
{
    this->_tileset = tileset;
    return 0;
}