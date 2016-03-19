//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_MEDIAHANDLER_H
#define MAPEDITINGTOOL_MEDIAHANDLER_H

# include <string>
# include <SFML/Graphics.hpp>

class MediaHandler
{
public:
    MediaHandler() {};
    ~MediaHandler() {};
    const int   loadNewTexture(const std::string &path, const std::string &name);
private:
    std::vector<std::pair<std::string &, const std::string &>> _textures;
    std::vector<std::pair<sf::Sprite &, const std::string &>>  _sprites;
};

#endif //MAPEDITINGTOOL_MEDIAHANDLER_H
