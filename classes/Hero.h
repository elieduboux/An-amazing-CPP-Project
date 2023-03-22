//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_HERO_H
#define MAZECPP_HERO_H

#include "Entity.h"
#include "CollisionMur.h"

class Hero : protected Entity{
    int NumberLife;
    bool haskey;
    CollisionMur collisionMur{};

public:
    Hero(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size,
         int numberLife);

    void takeKey();

    void useKey();

    const CollisionMur &getCollisionMur() const;

    void setCollisionMur(const CollisionMur &collisionMur);

    bool canGoUp(Debug * debug) const;

    bool canGoDown(Debug * debug) const;

    bool canGoLeft(Debug * debug) const;

    bool canGoRight(Debug * debug) const;

    //form entity
    V2 getPos();

    V2 getSize();

};


#endif //MAZECPP_HERO_H
