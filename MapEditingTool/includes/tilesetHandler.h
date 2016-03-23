//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_TILESETHANDLER_H
#define MAPEDITINGTOOL_TILESETHANDLER_H

# include <SFML/Graphics.hpp>
# include <fstream>
# include <string>

class TilesetHandler : public sf::Drawable, public sf::Transformable
{
public:
    TilesetHandler() {};
    ~TilesetHandler() {};
    const int       init(sf::Texture *tileset, sf::Vector2u tileSize, const std::string& level_path, unsigned int width=0, unsigned int height=0);
    const int       load(const std::string& level_path);
private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture     *_tileset;
    sf::VertexArray _vertices;
    //Properties
    int             _width;
    int             _height;
    int*            _tiles;
};

#endif //MAPEDITINGTOOL_TILESETHANDLER_H
