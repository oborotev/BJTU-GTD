//
// Created by storm on 19/03/16.
//

# include "tilesetHandler.h"
# include <iostream>
# include <sstream>

const int           TilesetHandler::init(sf::Texture *tileset, sf::Vector2u tileSize, const std::string& level_path, unsigned int width, unsigned int height)
{
    std::ifstream file(level_path);
    int           *tiles;
    bool        isFile = false;
    int         lineNumber = 0;

    if (width == 0 && height == 0)
    {
        unsigned int temp2 = 0;
        std::string temp;
        isFile = true;
        if (!file.is_open()) {
            std::cout << "Couldn't open the file on path : " << level_path << std::endl;
            return (1);
        }
        while (std::getline(file, temp))
        {
            std::stringstream ss(temp);
            lineNumber++;
            if (lineNumber == 1)
            {
                for (int i = 0; ss >> temp2; i++)
                {
                    if (i > 2)
                    {
                        std::cout << "Header misformatted for path " << level_path << std::endl;
                        return 1;
                    }
                    if (i == 0)
                        width = temp2;
                    else if (i == 1)
                        height = temp2;
                }
            }
            else if (lineNumber == 2)
            {
                tiles = new int[(width * height) + 1];
                int verifier;
                for (verifier = 0;ss >> temp2; verifier++)
                {
                    if (verifier > width * height)
                    {
                        std::cout << "Header doesn't match the file for path " << level_path << std::endl;
                        return 1;
                    }
                    tiles[verifier] = temp2;
                }
                if (verifier != width * height)
                {
                    std::cout << "Header doesn't match the file for path " << level_path << std::endl;
                    return 1;
                }
            }
            else if (lineNumber == 3)
            {
                std::cout << "File misformatted for path " << level_path << std::endl;
                return (1);
            }
        }
    }

    this->_tileset = tileset;

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];
            int tu = tileNumber % (_tileset->getSize().x / tileSize.x);
            int tv = tileNumber / (_tileset->getSize().x / tileSize.x);


            sf::Vertex* quad = &_vertices[(i + j * width) * 4];


            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    if (isFile)
     delete [] tiles;
    return 0;
}

void            TilesetHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = _tileset;
    target.draw(_vertices, states);
}