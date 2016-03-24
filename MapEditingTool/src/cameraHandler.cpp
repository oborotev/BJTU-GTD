//
// Created by storm on 23/03/16.
//

#include <iostream>
# include "cameraHandler.h"

void        CameraHandler::init(int windowWidth, int windowHeight, const sf::FloatRect &rect, const bool isDelimited, const sf::IntRect &delimitation)
{
    this->_windowHeight = windowHeight;
    this->_windowWidth = windowWidth;
    this->_camera = new sf::View(rect);
    this->_isDelimited = isDelimited;
    this->_delimitation = delimitation;
}

CameraHandler::~CameraHandler()
{
    delete this->_camera;
}

sf::View*   CameraHandler::getView() const
{
    return (this->_camera);
}

const int   CameraHandler::move(const float &x, const float &y) const
{
    float   xCamera = (this->_camera->getCenter().x - (this->_windowWidth / 2)) + x;
    float   yCamera = (this->_camera->getCenter().y - (this->_windowHeight / 2)) + y;
    sf::Vector2i     blocked = sf::Vector2i(0, 0);


    std::cout << "xCamera :" << xCamera << " yCamera: " << yCamera << std::endl;
    if (this->_isDelimited)
    {
        if (xCamera < this->_delimitation.left)
        {
            this->_camera->setCenter(this->_windowWidth / 2, this->_camera->getCenter().y);
            blocked.x = 1;
        }
        else if (xCamera > this->_delimitation.width)
        {
            this->_camera->setCenter(this->_delimitation.width + (this->_windowWidth / 2), this->_camera->getCenter().y);
            blocked.x = 1;
        }
        if (yCamera < this->_delimitation.top)
        {
            this->_camera->setCenter(this->_camera->getCenter().x, this->_windowHeight / 2);
            blocked.y = 1;
        }
        else if (yCamera > this->_delimitation.height)
        {
            this->_camera->setCenter(this->_camera->getCenter().x, this->_delimitation.height + (this->_windowHeight / 2));
            blocked.y = 1;
        }
    }
    if (!blocked.x)
        this->_camera->move(x, 0);
    if (!blocked.y)
        this->_camera->move(0, y);
    return (blocked.x || blocked.y);
}