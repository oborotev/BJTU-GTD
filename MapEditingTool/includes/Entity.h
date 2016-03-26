//
// Created by storm on 26/03/16.
//

#ifndef MAPEDITINGTOOL_ENTITY_H
#define MAPEDITINGTOOL_ENTITY_H

# include <string>

class Entity
{
public:
    Entity(const int &x, const int &y, const int &hp);
    ~Entity() {};
private:
    int     _hp;
    std::vector<const std::string> _dialogs;
    int     _x;
    int     _y;
};

#endif //MAPEDITINGTOOL_ENTITY_H
