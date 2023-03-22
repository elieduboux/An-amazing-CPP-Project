//
// Created by zen on 08/05/22.
//

#include "Momie.h"


Momie::Momie(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size,
             const V2 &dir) : Entity(textures, idTex, idTexs, pos, size), Dir(dir) {}

bool Momie::isCollisionMurMomie() const {
    return CollisionMurMomie;
}

void Momie::setCollisionMurMomie(bool collisionMurMomie) {
    CollisionMurMomie = collisionMurMomie;
}
