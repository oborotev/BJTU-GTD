# include "graphicHandler.h"

void    GraphicHandler::cameraOnEntity(Entity *entity)
{
    this->_cameraOnEntity = entity;
}

void             GraphicHandler::moveCamera(const Directions &direction)
{
    double       coef = (this->_cameraSpeed * 0.1) * this->_clock->getLastFrameTime().asMilliseconds();

    sf::Vector2i offset(0, 0);
    bool moved = false;

    if (direction == Directions::UP)
    {
        offset = this->_mainCamera->move(0.0, -coef, true);
        moved = true;
    }
    else if (direction == Directions::DOWN)
    {
        offset = this->_mainCamera->move(0.0, coef, true);
        moved = true;
    }
    else if (direction == Directions::LEFT)
    {
        offset = this->_mainCamera->move(-coef, 0.0, true);
        moved = true;
    }
    else if (direction == Directions::RIGHT)
    {
        offset = this->_mainCamera->move(coef, 0.0, true);
        moved = true;
    }
    this->_window->setView(*this->_mainCamera->getView());
    if (moved)
        this->moveStaticObjects();
}