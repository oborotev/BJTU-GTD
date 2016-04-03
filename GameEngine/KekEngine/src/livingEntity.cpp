//
// Created by storm on 26/03/16.
//

# include "livingEntity.h"

LivingEntity::LivingEntity(const int &x, const int &y, const int &hp, const float &speed, const bool animated, const sf::Time &animationSpeed, sf::Texture *spriteSheet) : Entity(x, y)
{
    this->_hp = hp;
    this->_animated = animated;
    this->_animationSpeed = animationSpeed;
    this->_speed = speed;
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