//
// Created by zen on 08/05/22.
//

#include "GameData.h"

GameData::GameData(int lMap, int hMap, int difficulty, const Hero &hero, const Key &key, const Chest &chest,
                   const vector<Momie> &momies) : LMap(lMap), HMap(hMap), Difficulty(difficulty), hero(hero), key(key),
                                                  chest(chest), momies(momies) {
    map = "MMMMMMMMMMMMMMM"
          "M M           M"
          "M M M MMM MMM M"
          "M   M       M M"
          "MMM M M MMM M M"
          "M   M M     M M"
          "M MMM MMM MMMMM"
          "M   M  M      M"
          "M M M  M M MM M"
          "M M M  M M M  M"
          "M M M MM M MMMM"
          "M M M    M    M"
          "M M M MMMMMMM M"
          "M M      M    M"
          "MMMMMMMMMMMMMMM";
}

bool GameData::Mur(int x, int y) {
    return map[(LMap - y - 1) * HMap + x] == 'M';
}

bool GameData::Mur(V2 cell) {
    return Mur(cell.x, cell.y);
}

void GameData::updateCollisionAvecUnMur() {


    float offset = 1;
    GameData::hero.getCollisionMur().setPUp(
            GameData::Mur(Entity::pxToCoor(GameData::hero.getPos().x,
                                           GameData::hero.getPos().y + GameData::hero.getSize().y + offset)) ||
            GameData::Mur(
                    Entity::pxToCoor(GameData::hero.getPos().x + GameData::hero.getSize().x,
                                     GameData::hero.getPos().y + GameData::hero.getSize().y + offset)));
    GameData::hero.getCollisionMur().setPDown(GameData::Mur(
            Entity::pxToCoor(GameData::hero.getPos().x, GameData::hero.getPos().y - offset)) ||
                                              GameData::Mur(Entity::pxToCoor(
                                                      GameData::hero.getPos().x + GameData::hero.getSize().x,
                                                      GameData::hero.getPos().y - offset)));
    GameData::hero.getCollisionMur().setPLeft(
            GameData::Mur(Entity::pxToCoor(GameData::hero.getPos().x - offset, GameData::hero.getPos().y)) ||
            GameData::Mur(Entity::pxToCoor(GameData::hero.getPos().x - offset,
                                           GameData::hero.getPos().y + GameData::hero.getSize().y)));
    GameData::hero.getCollisionMur().setPRight(GameData::Mur(
            Entity::pxToCoor(GameData::hero.getPos().x + GameData::hero.getSize().x + offset,
                             GameData::hero.getPos().y)) ||
                                               GameData::Mur(Entity::pxToCoor(
                                                       GameData::hero.getPos().x + GameData::hero.getSize().x + offset,
                                                       GameData::hero.getPos().y + GameData::hero.getSize().y)));
}
