//
// Created by storm on 26/03/16.
//

# include "livingEntity.h"
# include <iostream>

LivingEntity::LivingEntity(const int &x, const int &y, const int &hp, const float &speed, const bool animated, const sf::Time &animationSpeed, sf::Texture *spriteSheet) : Entity(x, y)
{
    this->_hp = hp;
    this->_currentHp = hp;
    this->_animated = animated;
    this->_animationSpeed = animationSpeed;
    this->_speed = speed;
    this->_active = true;
    if (spriteSheet)
    {
        for (int i = 0; i < this->_animations.size(); i++) {
            this->_animations[i] = new Animation();
            this->_animations[i]->setSpriteSheet(*spriteSheet);
        }
        this->_animation = new AnimatedSprite(animationSpeed, false, true);
        this->_animation->setPosition(x, y);
    }
    this->_direction = Direction::STILL;
}

void    LivingEntity::addFrameState(const LivingEntity::Direction &direction, const sf::IntRect &rect)
{
    if (direction != LivingEntity::Direction::DirectionCount)
    {
        this->_animations[direction]->addFrame(rect);
        if (direction == LivingEntity::Direction::STILL)
            this->_animation->play(*this->_animations[LivingEntity::Direction::STILL]);
    }
}

void    LivingEntity::setY(const float &y)
{
    this->_y = y;
    this->_animation->setPosition(this->_x, y);
}

void    LivingEntity::setX(const float &x)
{
    this->_x = x;
    this->_animation->setPosition(x, this->_y);
}

void    LivingEntity::setPosition(const double &x, const double &y)
{
    this->_x = x;
    this->_y = y;
    this->_animation->setPosition(x, y);
}

void    LivingEntity::setXYstandalone(const double &x, const double &y)
{
    this->_x = x;
    this->_y = y;
}

void    LivingEntity::changeDirection(const LivingEntity::Direction &direction)
{
    this->_direction = direction;
    this->_animation->play(*this->_animations[direction]);
    this->_animation->setLooped(true);
}

void    LivingEntity::move(const float &x, const float &y)
{
    this->_x += x;
    this->_y += y;
    this->_animation->move(x, y);
}

void    LivingEntity::update(const sf::Time &time)
{
    this->_animation->update(time);
}

AnimatedSprite* LivingEntity::getAnimation() const
{
    return this->_animation;
}

const float &LivingEntity::getSpeed() const
{
  return this->_speed;
}

void        LivingEntity::setSpeed(const float &speed)
{
    this->_speed = speed;
}

void        LivingEntity::setPhysicBody(b2Body *body, sf::Sprite *sprite)
{
    this->_body = std::make_pair(body, sprite);
}

sf::Sprite *LivingEntity::getBodySprite() const
{
    return (this->_body.second);
}

b2Body      *LivingEntity::getBody() const
{
    return (this->_body.first);
}

void        LivingEntity::updateBody(const bool disableAngularVelocity)
{
    if (disableAngularVelocity) {
        this->_body.first->SetAngularVelocity(0);
        this->_body.first->SetTransform(this->_body.first->GetPosition(), 0);
    }
    this->_x = this->_body.first->GetPosition().x;
    this->_y = this->_body.first->GetPosition().y;
    this->_body.second->setOrigin(8.f, 8.f);
    this->_body.second->setPosition(this->_body.first->GetPosition().x, this->_body.first->GetPosition().y);
    this->_body.second->setRotation(180/b2_pi * this->_body.first->GetAngle());
}

void        LivingEntity::moveBody(const sf::Vector2f &vector, b2Body* constraint)
{
    if (vector.x != 0)
        this->_body.first->SetLinearVelocity(b2Vec2(vector.x * 30, this->_body.first->GetLinearVelocity().y));
    else
        this->_body.first->SetLinearVelocity(b2Vec2(this->_body.first->GetLinearVelocity().x, vector.y * 30));
}

const bool  LivingEntity::getActive() const
{
    return (this->_active);
}

void        LivingEntity::setActive(const bool active)
{
    this->_active = active;
    this->_body.first->SetActive(active);
}