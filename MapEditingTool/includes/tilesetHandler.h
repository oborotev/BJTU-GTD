//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_TILESETHANDLER_H
#define MAPEDITINGTOOL_TILESETHANDLER_H

# include <SFML/Graphics.hpp>

class TilesetHandler : public sf::Drawable, public sf::Transformable
{
public:
    TilesetHandler() {};
    ~TilesetHandler() {};
    const int       init(const sf::Texture &tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture     _tileset;
    sf::VertexArray _vertices;
};

#endif //MAPEDITINGTOOL_TILESETHANDLER_H
