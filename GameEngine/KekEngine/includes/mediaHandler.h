//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_MEDIAHANDLER_H
#define MAPEDITINGTOOL_MEDIAHANDLER_H

# include <string>
# include <iostream>
# include <SFML/Graphics.hpp>
# include "Collision.h"

class MediaHandler
{
public:
    typedef struct s_staticParameters
    {
        std::string name;
        sf::Vector2f offsets;
    }              t_staticParameters;
public:
    MediaHandler() {};
    ~MediaHandler() {};
    const int   addNewTexture(const std::string &path, const std::string &name);
    const int   addNewFont(const std::string &path, const std::string &name);
    const int   addNewSprite(sf::Texture *texture, const std::string &spriteName, const bool isGui=false, const sf::Vector2i &position=sf::Vector2i(0, 0));
    const int   addNewShape(sf::Shape *shape, const std::string &shapeName, const bool isGui=false, const sf::Vector2i &position=sf::Vector2i(0, 0));
    sf::Shape   *getShape(const std::string &name);
    sf::Texture *getTexture(const std::string &name);
    sf::Font    *getFont(const std::string &name);
    sf::Sprite  *getSprite(const std::string &name);
    std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>> &getStaticElems();
    //Clean the vectors
    void        wipeAll();

private:
    std::vector<std::pair<sf::Texture *, const std::string>>  _textures;
    std::vector<std::pair<sf::Font *, const std::string>>     _fonts;
    std::vector<std::pair<sf::Sprite *, const std::string>>   _sprites;
    std::vector<std::pair<sf::Shape *, const std::string>>    _shapes;
    std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>> _staticElems;
};

#endif //MAPEDITINGTOOL_MEDIAHANDLER_H
