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

const sf::Vector2i   CameraHandler::move(const float &x, const float &y) const
{
    float   xCamera = (this->_camera->getCenter().x - (this->_windowWidth / 2)) + x;
    float   yCamera = (this->_camera->getCenter().y - (this->_windowHeight / 2)) + y;
    sf::Vector2i     blocked(0, 0);
    std::pair<bool, bool>             isBlocked = std::make_pair(false, false);

    std::cout << "xCamera :" << xCamera << " yCamera: " << yCamera << std::endl;
    if (this->_isDelimited)
    {
        if (xCamera < this->_delimitation.left)
        {
            this->_camera->setCenter(this->_windowWidth / 2, this->_camera->getCenter().y);
            blocked.x = 0;
            isBlocked.first = true;
        }
        else if (xCamera > this->_delimitation.width)
        {
            this->_camera->setCenter(this->_delimitation.width + (this->_windowWidth / 2), this->_camera->getCenter().y);
            blocked.x = 0;
            isBlocked.first = true;
        }
        if (yCamera < this->_delimitation.top)
        {
            this->_camera->setCenter(this->_camera->getCenter().x, this->_windowHeight / 2);
            blocked.y = 0;
            isBlocked.second = true;
        }
        else if (yCamera > this->_delimitation.height)
        {
            this->_camera->setCenter(this->_camera->getCenter().x, this->_delimitation.height + (this->_windowHeight / 2));
            blocked.y = 0;
            isBlocked.second = true;
        }
    }
    if (!isBlocked.first)
    {
        this->_camera->move(x, 0);
        blocked.x = x;
    }
    if (!isBlocked.second)
    {
        this->_camera->move(0, y);
        blocked.y = y;
    }
    return (blocked);
}