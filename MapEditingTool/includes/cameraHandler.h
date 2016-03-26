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
    void        init(int windowWidth, int windowHeight, const sf::FloatRect &rect, const bool isDelimited=false, const sf::IntRect &delimitation=sf::IntRect(0, 0, 0, 0));
    sf::View*   getView() const;
    const float &getCenterX() const;
    const float &getCenterY() const;
    void        updatePositionCenter(const float &x, const float &y);
    void        updatePositionCenter();
    void        updateWindowSize(const int &windowWidth, const int &windowHeight);
    void        setDelimitation(const sf::IntRect& delimitation);
    void        arbitraryMove(const float &x, const float &y);
    const sf::Vector2i  move(const float &x, const float &y, const bool updateNow=false);
private:
    sf::View    *_camera;
    bool            _isDelimited;
    sf::IntRect     _delimitation;
    int           _windowWidth;
    int           _windowHeight;
    float         _centerX;
    float         _centerY;
};

#endif //MAPEDITINGTOOL_CAMERAHANDLER_H
