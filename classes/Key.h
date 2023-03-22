//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_KEY_H
#define MAZECPP_KEY_H

#include "Entity.h"

class Key : protected Entity{
public:
    Key(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size);
};


#endif //MAZECPP_KEY_H
