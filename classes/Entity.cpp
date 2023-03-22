//
// Created by zen on 08/05/22.
//

#include "Entity.h"

Entity::Entity(const vector<string> &textures, int idTex, const vector<int> &idTexs, const V2 &pos, const V2 &size)
        : textures(textures), IdTex(idTex), IdTexs(idTexs), Pos(pos), Size(size) {

}

bool Entity::hitboxtouch( V2 posObj2, V2 sizeObj2) {
    return (Entity::Pos.x <= posObj2.x + sizeObj2.x &&
            Entity::Pos.x + Entity::Size.x >= posObj2.x &&
            Entity::Pos.y <= posObj2.y + sizeObj2.y &&
            Entity::Size.y + Entity::Pos.y >= posObj2.y);
}

void Entity::disappear() {
    Size = Size * 0;
    Pos = Pos * 0;
}

const V2 &Entity::getSize() const {
    return Size;
}

void Entity::setSize(const V2 &size) {
    Size = size;
}

const V2 &Entity::getPos() const {
    return Pos;
}

void Entity::setPos(const V2 &pos) {
    Pos = pos;
}
