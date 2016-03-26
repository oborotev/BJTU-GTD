//
// Created by storm on 26/03/16.
//

# include "livingEntity.h"

LivingEntity::LivingEntity(const int &x, const int &y, const int &hp, const bool animated, const sf::Time &animationSpeed, sf::Texture *spriteSheet) : Entity(x, y)
{
    this->_hp = hp;
    this->_animated = animated;
    this->_animationSpeed = animationSpeed;
    if (spriteSheet)
    {
        for (int i = 0; i < this->_animations.size(); i++) {
            this->_animations[i] = new Animation();
            this->_animations[i]->setSpriteSheet(*spriteSheet);
        }
        this->_animation = new AnimatedSprite(animationSpeed, true, false);
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

void    LivingEntity::changeDirection(const LivingEntity::Direction &direction)
{
    if (direction != LivingEntity::Direction::DirectionCount)
    {
        this->_direction = direction;
        this->_animation->play(*this->_animations[direction]);
    }
}

void    LivingEntity::move(const float &x, const float &y)
{
    this->_x = x;
    this->_y = y;
    this->_animation->setPosition(x, y);
}

void    LivingEntity::update(const sf::Time &time)
{
    this->_animation->update(time);
}

AnimatedSprite* LivingEntity::getAnimation()
{
    return this->_animation;
}