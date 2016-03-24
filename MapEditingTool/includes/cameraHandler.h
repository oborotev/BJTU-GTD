//
// Created by storm on 23/03/16.
//

#ifndef MAPEDITINGTOOL_CAMERAHANDLER_H
#define MAPEDITINGTOOL_CAMERAHANDLER_H

# include <SFML/Graphics.hpp>

class CameraHandler
{
public:
    CameraHandler() {};
    ~CameraHandler();
    void        init(const sf::FloatRect &rect);
    sf::View*   getView() const;
private:
    sf::View    *_camera;
};

#endif //MAPEDITINGTOOL_CAMERAHANDLER_H
