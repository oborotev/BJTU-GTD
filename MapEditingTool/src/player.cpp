//
// Created by storm on 26/03/16.
//

# include "player.h"

Player::Player(const int &x, const int &y, const int &hp, const float &speed, const bool animated, const sf::Time &animationSpeed, sf::Texture *spriteSheet) : LivingEntity(x, y, hp, speed, animated, animationSpeed, spriteSheet)
{}