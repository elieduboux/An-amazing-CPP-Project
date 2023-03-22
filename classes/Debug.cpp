//
// Created by zen on 08/05/22.
//

#include "Debug.h"

bool Debug::isNoclip() {
    return noclip;
}

void Debug::setNoclip(bool noclip) {
    Debug::noclip = noclip;
}

bool Debug::isHitbox() {
    return hitbox;
}

void Debug::setHitbox(bool hitbox) {
    Debug::hitbox = hitbox;
}

Debug::Debug() {
    Debug::hitbox = false;
    Debug::noclip = false;
}
