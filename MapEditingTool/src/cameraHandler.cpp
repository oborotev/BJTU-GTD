//
// Created by storm on 23/03/16.
//

# include "cameraHandler.h"

void        CameraHandler::init(const sf::FloatRect &rect)
{
    this->_camera = new sf::View(rect);
}

CameraHandler::~CameraHandler()
{
    delete this->_camera;
}

sf::View*   CameraHandler::getView() const
{
    return (this->_camera);
}

