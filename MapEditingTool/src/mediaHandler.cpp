//
// Created by storm on 19/03/16.
//

# include "mediaHandler.h"

void        MediaHandler::wipeAll()
{
    for (std::vector<std::pair<sf::Texture *, const std::string>>::iterator it = this->_textures.begin(); it != this->_textures.end(); ++it)
        delete it->first;
    this->_textures.clear();
    for (std::vector<std::pair<sf::Sprite *, const std::string>>::iterator it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
        delete it->first;
    this->_sprites.clear();
}

const int   MediaHandler::addNewTexture(const std::string &path, const std::string &name)
{
    this->_textures.emplace_back(std::make_pair(new sf::Texture, name));
    if (!this->_textures.back().first->loadFromFile(path))
    {
        delete this->_textures.back().first;
        std::cout << "Problem while loading the texture" << std::endl;
        return (1);
    }
    return (0);
}

const int   MediaHandler::addNewSprite(const std::string &textureName)
{
    std::cout << _textures.size() << std::endl;
  /*  for(unsigned int i = 0; i < _textures.size(); i++)
    {*/
    std::cout << this->_textures[0].second << std::endl;

    if (this->_textures[0].second == "test")
            std::cout << "ta" << std::endl;
   // }
/*
    sf::Sprite sprite;
    sprite.setTexture(texture);

    if (!texture.loadFromFile(path))
    {
        std::cout << "Problem while loading the texture";
        return (1);
    }
    this->_textures.push_back(std::make_pair(texture, name));
    //std::cout << this->_textures[0].second << std::endl;
    return (0);
*/
}

sf::Texture* MediaHandler::getTexture(const std::string &name)
{
    auto it = std::find_if(this->_textures.begin(), this->_textures.end(), [&name](const std::pair<sf::Texture *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_textures.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a texture for " << name << " in the registered textures" << std::endl;
        return (NULL);
    }
}

sf::Sprite  MediaHandler::getSprite(const std::string &name)
{

}
