//
// Created by zen on 08/05/22.
//

#include "Hero.h"


void Hero::takeKey() {
    Hero::haskey = true;
}

void Hero::useKey() {
    Hero::haskey = false;
}

Hero::Hero(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size,
           int numberLife) : Entity(textures, idTex, idTexs, pos, size), NumberLife(numberLife) {
        haskey = false;

}

bool Hero::canGoUp(Debug *debug) const {
    return Hero::collisionMur.canGoUp(debug);
}

bool Hero::canGoDown(Debug *debug) const {
    return Hero::collisionMur.canGoDown(debug);
}

bool Hero::canGoLeft(Debug *debug) const {
    return Hero::collisionMur.canGoLeft(debug);
}

bool Hero::canGoRight(Debug *debug) const {
    return Hero::collisionMur.canGoRight(debug);
}

const CollisionMur &Hero::getCollisionMur() const {
    return collisionMur;
}

void Hero::setCollisionMur(const CollisionMur &collisionMur) {
    Hero::collisionMur = collisionMur;
}

V2 Hero::getPos() {
    return Hero::Pos;
}

V2 Hero::getSize() {
    return Hero::Size;
}


