//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_COLLISIONMUR_H
#define MAZECPP_COLLISIONMUR_H


#include "Debug.h"

class CollisionMur {
    bool p_up;
    bool p_down;
    bool p_left;
    bool p_right;
public:

    CollisionMur();

    bool canGoUp(Debug * debug) const;

    bool canGoDown(Debug * debug) const;

    bool canGoLeft(Debug * debug) const;

    bool canGoRight(Debug * debug) const;

    bool isPUp() const;

    void setPUp(bool pUp) const;

    bool isPDown() const;

    void setPDown(bool pDown) const;

    bool isPLeft() const;

    void setPLeft(bool pLeft) const;

    bool isPRight() const;

    void setPRight(bool pRight) const;

};


#endif //MAZECPP_COLLISIONMUR_H
