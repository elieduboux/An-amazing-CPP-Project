//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_MOMIE_H
#define MAZECPP_MOMIE_H


#include "Entity.h"

class Momie: protected Entity{
    V2 Dir;
    bool CollisionMurMomie;
    V2 DirPossibles[4] = {V2(0, 1), V2(1, 0), V2(0, -1), V2(-1, 0)};
public:
    Momie(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size,
          const V2 &dir);

    bool isCollisionMurMomie() const;

    void setCollisionMurMomie(bool collisionMurMomie);
};


#endif //MAZECPP_MOMIE_H
