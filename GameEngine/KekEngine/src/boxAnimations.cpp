//
// Created by storm on 10/04/16.
//

# include "boxAnimations.h"
# include <iostream>

BoxAnimations::BoxAnimations(const sfx::FrameClock *clock)
{
    this->_clock = clock;
}

void BoxAnimations::init()
{
    this->_animators.insert(std::make_pair(BoxAnimations::ANIMATIONS::SIZE_CHANGE, &BoxAnimations::sizeChange));
}

const bool BoxAnimations::isAnimationRunning(const std::string &name)
{
    for (int i= 0; i < this->_animations.size(); i++)
    {
        if (this->_animations[i].name == name)
            return (true);
    }
    return (false);
}
void BoxAnimations::registerNewAnimation(const std::string &name, b2Body *body, const BoxAnimations::ANIMATIONS &animationType,
                                         std::vector<b2Vec2> currentSizes, std::vector<b2Vec2> currentPositions,
                                         std::vector<b2Vec2> &newSizes, std::vector<b2Vec2> &newPositions,
                                         const float &newAngle, const float &speed, const sf::Time &duration)
{
    t_animationComponents newComponent;

    newComponent.name = name;
    newComponent.body = body;
    newComponent.animationType = animationType;
    newComponent.currentSizes = currentSizes;
    newComponent.currentPositions = currentPositions;
    newComponent.newSizes = newSizes;
    newComponent.newPositions = newPositions;
    newComponent.newAngle = newAngle;
    newComponent.speed = speed;
    newComponent.duration = duration;
    this->_animations.push_back(newComponent);
    return ;
}

bool     BoxAnimations::sizeChange(std::vector<t_animationComponents>::iterator animation)
{
    bool changed = false;
    float coef = static_cast<float>((animation->speed * 0.1) * this->_clock->getLastFrameTime().asMilliseconds());
    std::array<float32, 4> frictions;
    int i = 0;

    for (b2Fixture* f = animation->body->GetFixtureList(); f;)
    {
        b2Fixture* fixtureToDestroy = f;
        frictions[i] = f->GetFriction();
        f = f->GetNext();
        animation->body->DestroyFixture(fixtureToDestroy);
        i++;
    }
    for (i=0; i < 4; i++)
    {
        b2PolygonShape polygonShape;
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.friction = frictions[i];
        //Sizes
        if (animation->currentSizes[i].x < animation->newSizes[i].x) {
            animation->currentSizes[i].x =
                    animation->currentSizes[i].x + coef > animation->newSizes[i].x ? animation->newSizes[i].x :
                    animation->currentSizes[i].x + coef;
            changed = true;
        }
        else if (animation->currentSizes[i].x > animation->newSizes[i].x) {
            animation->currentSizes[i].x =
                    animation->currentSizes[i].x - coef < animation->newSizes[i].x ? animation->newSizes[i].x :
                    animation->currentSizes[i].x - coef;
            changed = true;
        }
        if (animation->currentSizes[i].y < animation->newSizes[i].y) {
            animation->currentSizes[i].y =
                    animation->currentSizes[i].y + coef > animation->newSizes[i].y ? animation->newSizes[i].y :
                    animation->currentSizes[i].y + coef;
            changed = true;
        }
        else if (animation->currentSizes[i].y > animation->newSizes[i].y) {
            animation->currentSizes[i].y =
                    animation->currentSizes[i].y - coef < animation->newSizes[i].y ? animation->newSizes[i].y :
                    animation->currentSizes[i].y - coef;
            changed = true;
        }
        //Positions
        if (animation->currentPositions[i].x < animation->newPositions[i].x) {
            animation->currentPositions[i].x =
                    animation->currentPositions[i].x + coef > animation->newPositions[i].x
                    ? animation->newPositions[i].x : animation->currentPositions[i].x + coef;
            changed = true;
        }
        else if (animation->currentPositions[i].x > animation->newPositions[i].x) {
            animation->currentPositions[i].x =
                    animation->currentPositions[i].x - coef < animation->newPositions[i].x
                    ? animation->newPositions[i].x : animation->currentPositions[i].x - coef;
            changed = true;
        }
        if (animation->currentPositions[i].y < animation->newPositions[i].y) {
            animation->currentPositions[i].y =
                    animation->currentPositions[i].y + coef > animation->newPositions[i].y
                    ? animation->newPositions[i].y : animation->currentPositions[i].y + coef;
            changed = true;
        }
        else if (animation->currentPositions[i].y > animation->newPositions[i].y) {
            animation->currentPositions[i].y =
                    animation->currentPositions[i].y - coef < animation->newPositions[i].y
                    ? animation->newPositions[i].y : animation->currentPositions[i].y - coef;
            changed = true;
        }
        polygonShape.SetAsBox(animation->currentSizes[i].x, animation->currentSizes[i].y, animation->currentPositions[i], animation->newAngle);
        animation->body->CreateFixture(&myFixtureDef);
    }
    return (changed);
}

void BoxAnimations::animationsHandler()
{
    for (std::vector<t_animationComponents>::iterator it = this->_animations.begin() ; it != this->_animations.end(); ++it) {
        //std::cout << "There is an animation" << std::endl;
        if (this->_animations.size() < 1)
            break ;

        if (!(this->*_animators[it->animationType])(it))
            this->_animations.erase(it);
    }
}

void BoxAnimations::terminate()
{
}