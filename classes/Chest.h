//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_CHEST_H
#define MAZECPP_CHEST_H

#include "Entity.h"

class Chest: protected Entity{
public:
    Chest(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size);
};


#endif //MAZECPP_CHEST_H
