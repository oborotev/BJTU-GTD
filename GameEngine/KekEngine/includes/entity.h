//
// Created by storm on 26/03/16.
//

#ifndef MAPEDITINGTOOL_ENTITY_H
#define MAPEDITINGTOOL_ENTITY_H

# include <string>
# include <vector>

class Entity
{
public:
    Entity(const int &x, const int &y);
    ~Entity() {};
    const int &getX();
    const int &getY();
    void    setY(const double &y);
    void    setX(const double &x);
protected:
    std::vector<std::string> _dialogs;
    int     _x;
    int     _y;
};

#endif //MAPEDITINGTOOL_ENTITY_H
