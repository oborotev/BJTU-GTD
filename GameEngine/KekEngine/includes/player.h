//
// Created by storm on 26/03/16.
//

#ifndef MAPEDITINGTOOL_PLAYER_H
#define MAPEDITINGTOOL_PLAYER_H

# include "livingEntity.h"

class Player : public LivingEntity
{
public:
    Player(const int &x, const int &y, const int &hp, const float &speed=10.0, const bool animated=false, const sf::Time &animationSpeed=sf::Time::Zero, sf::Texture *spriteSheet=NULL);
    ~Player() {}
};

#endif //MAPEDITINGTOOL_PLAYER_H
