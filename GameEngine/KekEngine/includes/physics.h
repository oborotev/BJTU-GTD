//
// Created by storm on 02/04/16.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H

# include <SFML/Graphics.hpp>
# include <Box2D/Box2D.h>
# include <map>
# include <string>

class PhysicsHandler
{
public:
    const bool init(const sf::Vector2f &gravity);
    void    registerNewBody(b2Body *body, const std::string &name);
    b2Body *getBody(const std::string &name);
    b2World *getWorld() const;
    void terminate();
private:
    b2World *_world;
    std::map<std::string, b2Body *> _bodies;
};

#endif //GAMEENGINE_PHYSICS_H
