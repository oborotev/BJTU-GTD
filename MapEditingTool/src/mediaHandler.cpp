//
// Created by storm on 19/03/16.
//

# include "mediaHandler.h"

const int   MediaHandler::addNewTexture(const std::string &path, const std::string &name)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "Problem while loading the texture";
        return (1);
    }
    this->_textures.push_back(std::make_pair(texture, name));
    //std::cout << this->_textures[0].second << std::endl;
    return (0);
}

const int   MediaHandler::addNewSprite(const std::string &textureName)
{

}

sf::Texture MediaHandler::getTexture(const std::string &name)
{

}

sf::Sprite  MediaHandler::getSprite(const std::string &name)
{

}
