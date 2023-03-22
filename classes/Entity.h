//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_ENTITY_H
#define MAZECPP_ENTITY_H

#include <vector>
#include <string>
#include "../V2.h"
#include "GameData.h"

using namespace std;

class Entity {
    vector<string> textures;
    int IdTex;
    vector<int> IdTexs;

protected:
    V2 Size;
    V2 Pos;
public:
    Entity(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size);

    bool hitboxtouch(V2 posObj2, V2 sizeObj2);

    static V2 pxToCoor(int x, int y) { return V2((int) x / Lpix, (int) y / Lpix); }

    static V2 pxToCoor(V2 coor) { return pxToCoor((int) coor.x / Lpix, (int) coor.y / Lpix); }

    static V2 coorToPx(int x, int y) { return V2(x * Lpix + Lpix / 2, y * Lpix + Lpix / 2); }

    static V2 coorToPx(V2 coor) { return coorToPx(coor.x, coor.y); }

    const V2 &getSize() const;

    void setSize(const V2 &size);

    const V2 &getPos() const;

    void setPos(const V2 &pos);

    void disappear();
};

#endif //MAZECPP_ENTITY_H
