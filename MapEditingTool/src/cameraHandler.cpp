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
    this->_centerX = this->_camera->getCenter().x;
    this->_centerY = this->_camera->getCenter().y;
}

CameraHandler::~CameraHandler()
{
    delete this->_camera;
}

sf::View*   CameraHandler::getView() const
{
    return (this->_camera);
}

const float     &CameraHandler::getCenterX() const {
    return (this->_centerX);
}

const float     &CameraHandler::getCenterY() const {
    return (this->_centerY);
}

void        CameraHandler::updateWindowSize(const int &windowWidth, const int &windowHeight)
{
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
}

void        CameraHandler::setDelimitation(const sf::IntRect &delimitation)
{
    this->_delimitation = delimitation;
    this->_isDelimited =
            delimitation.height != 0 || delimitation.top != 0 || delimitation.left != 0 || delimitation.width != 0;
}

void        CameraHandler::arbitraryMove(const float &x, const float &y)
{
    this->_centerX += x;
    this->_centerY += y;
    this->_camera->move(x, y);
}

void        CameraHandler::updatePositionCenter(const float &x, const float &y)
{
    this->_camera->setCenter(x, y);
}

void        CameraHandler::updatePositionCenter()
{
    this->_camera->setCenter(this->_centerX, this->_centerY);
}

const sf::Vector2i   CameraHandler::move(const float &x, const float &y, const bool updateNow)
{
    float   xCamera = (this->_centerX - (this->_windowWidth / 2)) + x;
    float   yCamera = (this->_centerY - (this->_windowHeight / 2)) + y;
    sf::Vector2i     blocked(0, 0);
    std::pair<bool, bool>             isBlocked = std::make_pair(false, false);

    if (this->_isDelimited)
    {
        if (xCamera < this->_delimitation.left)
        {
            this->_centerX = this->_windowWidth / 2;
            blocked.x = 0;
            isBlocked.first = true;
        }
        else if (xCamera > this->_delimitation.width)
        {
            this->_centerX = this->_delimitation.width + (this->_windowWidth / 2);
            blocked.x = 0;
            isBlocked.first = true;
        }
        if (yCamera < this->_delimitation.top)
        {
            this->_centerY = this->_windowHeight / 2;
            blocked.y = 0;
            isBlocked.second = true;
        }
        else if (yCamera > this->_delimitation.height)
        {
            this->_centerY = this->_delimitation.height + (this->_windowHeight / 2);
            blocked.y = 0;
            isBlocked.second = true;
        }
    }
    if (!isBlocked.first)
    {
        this->_centerX += x;
        blocked.x = static_cast<int>(x);
    }
    if (!isBlocked.second)
    {
        this->_centerY += y;
        blocked.y = static_cast<int>(y);
    }
    if (updateNow)
        this->updatePositionCenter();
    return (blocked);
}