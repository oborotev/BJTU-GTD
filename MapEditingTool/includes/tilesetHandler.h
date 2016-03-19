//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_TILESETHANDLER_H
#define MAPEDITINGTOOL_TILESETHANDLER_H

# include <SFML/Graphics.hpp>

class TilesetHandler
{
public:
    TilesetHandler() {};
    ~TilesetHandler() {};
    const int       init(const sf::Texture &tileset);
private:
    sf::Texture     _tileset;
};

#endif //MAPEDITINGTOOL_TILESETHANDLER_H
