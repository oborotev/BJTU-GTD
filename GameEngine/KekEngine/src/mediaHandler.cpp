//
// Created by storm on 19/03/16.
//

# include "mediaHandler.h"

void        MediaHandler::wipeAll()
{
    for (std::vector<std::pair<sf::Texture *, const std::string>>::iterator it = this->_textures.begin(); it != this->_textures.end(); ++it)
        delete it->first;
    this->_textures.clear();
    for (std::vector<std::pair<sf::Font *, const std::string>>::iterator it = this->_fonts.begin(); it != this->_fonts.end(); ++it)
        delete it->first;
    this->_fonts.clear();
    for (std::vector<std::pair<sf::Sprite *, const std::string>>::iterator it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
        delete it->first;
    this->_sprites.clear();
    for (std::vector<std::pair<sf::Shape *, const std::string>>::iterator it = this->_shapes.begin(); it != this->_shapes.end(); ++it)
        delete it->first;
    for (std::vector<std::pair<sf::Sound *, const std::string>>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it)
        delete it->first;
    for (std::vector<std::pair<sf::SoundBuffer *, const std::string>>::iterator it = this->_soundBuffers.begin(); it != this->_soundBuffers.end(); ++it)
        delete it->first;
    this->_shapes.clear();
    this->_staticElems.clear();
}

const int   MediaHandler::addNewSound(const std::string &path, const std::string &name)
{
    this->_soundBuffers.emplace_back(std::make_pair(new sf::SoundBuffer, name));
    if (!this->_soundBuffers.back().first->loadFromFile(path))
    {
        std::cout << "Problem while loading the sound" << std::endl;
        return (1);
    }
    this->_sounds.emplace_back(std::make_pair(new sf::Sound, name));
    this->_sounds.back().first->setBuffer(*this->_soundBuffers.back().first);
    return (0);
}

const int   MediaHandler::addNewTexture(const std::string &path, const std::string &name)
{
    this->_textures.emplace_back(std::make_pair(new sf::Texture, name));
    if (!Collision::CreateTextureAndBitmask(this->_textures.back().first, path))
    {
        delete this->_textures.back().first;
        std::cout << "Problem while loading the texture" << std::endl;
        return (1);
    }
    return (0);
}

const int   MediaHandler::addNewFont(const std::string &path, const std::string &name)
{
    this->_fonts.emplace_back(std::make_pair(new sf::Font, name));
    if (! this->_fonts.back().first->loadFromFile(path))
    {
        std::cout << "Problem while loading the font" << std::endl;
        delete this->_fonts.back().first;
        return (1);
    }
    return (0);
}

const int   MediaHandler::addNewShape(sf::Shape *shape, const std::string &name, const bool isGui, const sf::Vector2i &position)
{
    if (isGui)
    {
        MediaHandler::t_staticParameters staticParams;

        staticParams.name = name;
        staticParams.offsets = sf::Vector2f(position.x, position.y);
        this->_staticElems.emplace_back(std::make_pair(shape, staticParams));
        this->_staticElems.back().first->setPosition(staticParams.offsets.x, staticParams.offsets.y);
    }
    this->_shapes.emplace_back(std::make_pair(shape, name));
    return (0);
}

std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>>   &MediaHandler::getStaticElems()
{
    return (this->_staticElems);
}

const int   MediaHandler::addNewSprite(sf::Texture *texture, const std::string &spriteName,  const sf::IntRect &textureRect, const bool isGui, const sf::Vector2i &position)
{
    this->_sprites.emplace_back(std::make_pair(new sf::Sprite, spriteName));
    this->_sprites.back().first->setTexture(*texture);
    if (textureRect.height != 0 && textureRect.width != 0)
        this->_sprites.back().first->setTextureRect(textureRect);
    if (isGui)
    {
        MediaHandler::t_staticParameters staticParams;

        staticParams.name = spriteName;
        staticParams.offsets = sf::Vector2f(position.x, position.y);
        this->_staticElems.emplace_back(std::make_pair(this->_sprites.back().first, staticParams));
        this->_staticElems.back().first->setPosition(staticParams.offsets.x, staticParams.offsets.y);
    }
    return (0);
}

sf::Shape* MediaHandler::getShape(const std::string &name)
{
    if (this->_shapes.size() == 0)
        return (NULL);
    auto it = std::find_if(this->_shapes.begin(), this->_shapes.end(), [&name](const std::pair<sf::Shape *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_shapes.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a texture for " << name << " in the registered textures" << std::endl;
        return (NULL);
    }
}

sf::Texture* MediaHandler::getTexture(const std::string &name)
{
    if (this->_textures.size() == 0)
        return (NULL);
    auto it = std::find_if(this->_textures.begin(), this->_textures.end(), [&name](const std::pair<sf::Texture *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_textures.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a texture for " << name << " in the registered textures" << std::endl;
        return (NULL);
    }
}

sf::Font* MediaHandler::getFont(const std::string &name)
{
    if (this->_fonts.size() == 0)
        return (NULL);
    auto it = std::find_if(this->_fonts.begin(), this->_fonts.end(), [&name](const std::pair<sf::Font *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_fonts.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a font for " << name << " in the registered fonts" << std::endl;
        return (NULL);
    }
}

sf::Sound* MediaHandler::getSound(const std::string &name)
{
    if (this->_sounds.size() == 0)
        return (NULL);
    auto it = std::find_if(this->_sounds.begin(), this->_sounds.end(), [&name](const std::pair<sf::Sound *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_sounds.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a sound for " << name << " in the registered sounds" << std::endl;
        return (NULL);
    }
}

sf::Sprite*  MediaHandler::getSprite(const std::string &name)
{
    if (this->_sprites.size() == 0)
        return (NULL);
    auto it = std::find_if(this->_sprites.begin(), this->_sprites.end(), [&name](const std::pair<sf::Sprite *, const std::string>& obj) {return obj.second == name;});
    if (it != this->_sprites.end())
        return (it->first);
    else
    {
        std::cout << "Couldn't find a sprite for " << name << " in the registered sprites" << std::endl;
        return (NULL);
    }
}
