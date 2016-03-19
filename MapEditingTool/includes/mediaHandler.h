//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_MEDIAHANDLER_H
#define MAPEDITINGTOOL_MEDIAHANDLER_H

# include <string>
# include <iostream>
# include <SFML/Graphics.hpp>

class MediaHandler
{
public:
    MediaHandler() {};
    ~MediaHandler() {};
    const int   addNewTexture(const std::string &path, const std::string &name);
    const int   addNewSprite(const std::string &textureName);
    sf::Texture getTexture(const std::string &name);
    sf::Sprite  getSprite(const std::string &name);

private:
    std::vector<std::pair<const sf::Texture &, const std::string>> _textures;
    std::vector<std::pair<sf::Sprite &, const std::string>>  _sprites;
};

#endif //MAPEDITINGTOOL_MEDIAHANDLER_H
