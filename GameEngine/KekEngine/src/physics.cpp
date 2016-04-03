//
// Created by storm on 02/04/16.
//

#include "physics.h"

void  PhysicsHandler::terminate()
{
    this->_bodies.clear();
    delete this->_world;
}

const bool  PhysicsHandler::init(const sf::Vector2f &gravity)
{
    this->_world = new b2World(b2Vec2(gravity.x, gravity.y));
    if (this->_world == nullptr)
        return (false);
    return (true);
}

void    PhysicsHandler::registerNewBody(b2Body *body, const std::string &name)
{
    this->_bodies[name] = body;
}

b2Body  *PhysicsHandler::getBody(const std::string &name)
{
    return (this->_bodies[name]);
}

b2World *PhysicsHandler::getWorld() const
{
    return (this->_world);
}