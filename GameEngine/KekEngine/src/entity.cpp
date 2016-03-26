//
// Created by storm on 26/03/16.
//

# include "entity.h"

Entity::Entity(const int &x, const int &y)
{
    this->_x = x;
    this->_y = y;
}

const int &Entity::getX()
{
    return (this->_x);
}

const int &Entity::getY()
{
    return (this->_y);
}