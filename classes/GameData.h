//
// Created by zen on 08/05/22.
//

#ifndef MAZECPP_GAMEDATA_H
#define MAZECPP_GAMEDATA_H

#include <string>
#include "../V2.h"
#include <vector>
#include "Entity.h"
#include "Hero.h"
#include "Key.h"
#include "Chest.h"
#include "Momie.h"

using namespace std;

const int Lpix = 40;  // largeur en pixels des cases du labyrinthe

class GameData {
    string map;
    int LMap;
    int HMap;
    int Difficulty;
    Hero hero;
    Key key;
    Chest chest;
    std::vector<Momie> momies;

public:
    GameData(int lMap, int hMap, int difficulty, const Hero &hero, const Key &key, const Chest &chest,
             const vector<Momie> &momies);

    bool Mur(int x, int y);
    bool Mur(V2 cell);
    void updateCollisionAvecUnMur();
};


#endif //MAZECPP_GAMEDATA_H
