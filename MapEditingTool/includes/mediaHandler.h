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
    const int   addNewShape(sf::Shape *shape, const std::string &shapeName);
    sf::Shape   *getShape(const std::string &name);
    sf::Texture *getTexture(const std::string &name);
    sf::Sprite  getSprite(const std::string &name);
    //Clean the vectors
    void        wipeAll();

private:
    std::vector<std::pair<sf::Texture *, const std::string>> _textures;
    std::vector<std::pair<sf::Sprite *, const std::string>>  _sprites;
    std::vector<std::pair<sf::Shape *, const std::string>>   _shapes;
};

#endif //MAPEDITINGTOOL_MEDIAHANDLER_H
