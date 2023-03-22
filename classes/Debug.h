//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_DEBUG_H
#define MAZECPP_DEBUG_H


class Debug {
    bool noclip;
    bool hitbox;
public:

    Debug();

    bool isNoclip();

    void setNoclip(bool noclip);

    bool isHitbox();

    void setHitbox(bool hitbox);
};


#endif //MAZECPP_DEBUG_H
