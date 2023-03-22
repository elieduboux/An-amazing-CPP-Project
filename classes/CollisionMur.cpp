//

#include "CollisionMur.h"

//
// Created by zen on 08/05/22.
CollisionMur::CollisionMur() {
    CollisionMur::p_up = false;
    CollisionMur::p_down = false;
    CollisionMur::p_left = false;
    CollisionMur::p_right = false;
}

bool CollisionMur::canGoUp(Debug *debug) const {
    return !p_up || debug->isNoclip();
}

bool CollisionMur::canGoDown(Debug *debug) const {
    return !p_down || debug->isNoclip();
}

bool CollisionMur::canGoLeft(Debug *debug) const {
    return !p_left || debug->isNoclip();
}

bool CollisionMur::canGoRight(Debug *debug) const {
    return !p_right || debug->isNoclip();
}

bool CollisionMur::isPUp() const {
    return p_up;
}

void CollisionMur::setPUp(bool pUp) const {
    p_up = pUp;
}

bool CollisionMur::isPDown() const {
    return p_down;
}

void CollisionMur::setPDown(bool pDown) const {
    p_down = pDown;
}

bool CollisionMur::isPLeft() const {
    return p_left;
}

void CollisionMur::setPLeft(bool pLeft) const {
    p_left = pLeft;
}

bool CollisionMur::isPRight() const {
    return p_right;
}

void CollisionMur::setPRight(bool pRight) const {
    p_right = pRight;
}

