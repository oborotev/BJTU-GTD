# include "graphicHandler.h"

void            GraphicHandler::moveStaticObjects(const bool mode)
{
    std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>> staticElems = this->_mediaHandler->getStaticElems();

    for (std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>>::iterator it = staticElems.begin(); it < staticElems.end(); it++)
    {
        it->first->setPosition(
                (this->_mainCamera->getCenterX() - (this->_modeWidth / 2)) + it->second.offsets.x,
                (this->_mainCamera->getCenterY() - (this->_modeHeight / 2)) +
                it->second.offsets.y);
    }
    //if (!mode)
    this->_clockHUD->setPosXY((this->_mainCamera->getCenterX() - (this->_modeWidth / 2)) + 800, (this->_mainCamera->getCenterY() - (this->_modeHeight / 2)) + 600);
    //else
        //this->_clockHUD->setPosXY(this->_mainCamera->getCenterX(), this->_mainCamera->getCenterY());
}

void        GraphicHandler::moveLivingEntity(LivingEntity *entity, const LivingEntity::Direction &direction, const bool &moveCamera, const bool &isPlayer)
{
    double       coef = (entity->getSpeed() * 0.1) * this->_clock->getLastFrameTime().asMilliseconds();
    bool         moved = false;
    float        entityX = entity->getX();
    float        entityY = entity->getY();

    if (direction == LivingEntity::Direction::UP &&
        !this->_baseMap->checkCollision(entity->getAnimation()->getSpriteFrame(), sf::Vector2<double>(entityX, entityY), coef, LivingEntity::Direction::UP, entity, this->_mainCamera))
    {
        if (moveCamera)
            this->_mainCamera->arbitraryMove(0, -coef);
        if (!_playerMoved)
            entity->changeDirection(LivingEntity::Direction::UP);
        entity->move(0, -coef);
        moved = true;
    }
    else if (direction == LivingEntity::Direction::DOWN &&
             !this->_baseMap->checkCollision(entity->getAnimation()->getSpriteFrame(), sf::Vector2<double>(entityX, entityY), coef, LivingEntity::Direction::DOWN, entity, this->_mainCamera))
    {
        if (moveCamera)
            this->_mainCamera->arbitraryMove(0, coef);
        if (!_playerMoved)
            entity->changeDirection(LivingEntity::Direction::DOWN);
        entity->move(0, coef);
        moved = true;
    }
    else if (direction == LivingEntity::Direction::LEFT &&
             !this->_baseMap->checkCollision(entity->getAnimation()->getSpriteFrame(), sf::Vector2<double>(entityX, entityY), coef, LivingEntity::Direction::LEFT, entity, this->_mainCamera))
    {
        if (moveCamera)
            this->_mainCamera->arbitraryMove(-coef, 0);
        if (!_playerMoved)
            entity->changeDirection(LivingEntity::Direction::LEFT);
        entity->move(-coef, 0);
        moved = true;
    }
    else if (direction == LivingEntity::Direction::RIGHT &&
             !this->_baseMap->checkCollision(entity->getAnimation()->getSpriteFrame(), sf::Vector2<double>(entityX, entityY), coef, LivingEntity::Direction::RIGHT, entity, this->_mainCamera))
    {
        if (moveCamera)
            this->_mainCamera->arbitraryMove(coef, 0);
        if (!_playerMoved)
            entity->changeDirection(LivingEntity::Direction::RIGHT);
        entity->move(coef, 0);
        moved = true;
    }
    if (direction == LivingEntity::Direction::RIGHT || direction == LivingEntity::Direction::LEFT || direction == LivingEntity::Direction::UP || direction == LivingEntity::Direction::DOWN)
    {
        _calledToMove = true;
        this->_window->setView(*this->_mainCamera->getView());
        this->moveStaticObjects(true);
    }
    if (isPlayer)
    {
        if (_calledToMove && _playerMoved)
            _playerMoved = true;
        else
            _playerMoved = moved;
    }
}