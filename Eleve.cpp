#pragma warning( disable : 4996 )

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <map>
#include <thread>
#include "glut.h"
#include "G2D.h"

using namespace std;
using namespace std::chrono;
using std::this_thread::sleep_for;


bool noclip = false;
bool hitbox = false;

struct _Heros {
    vector<string> textures = {
            "[RRR  ]"
            "[RRWR ]"
            "[RRR  ]"
            "[YY   ]"
            "[YYY  ]"
            "[YY YG]"
            "[GG   ]"
            "[CC   ]"
            "[pC   ]"
            "[p C  ]"
            "[p C  ]",
            "[RRR  ]"
            "[RRWR ]"
            "[RRR  ]"
            "[YY   ]"
            "[YYY  ]"
            "[YY YG]"
            "[GG   ]"
            "[CC   ]"
            "[Cp   ]"
            "[C p  ]"
            "[C p  ]",
            "[  RRR]"
            "[ RWRR]"
            "[  RRR]"
            "[   YY]"
            "[  YYY]"
            "[GY YY]"
            "[   GG]"
            "[   CC]"
            "[   pC]"
            "[  p C]"
            "[  p C]",
            "[  RRR]"
            "[ RWRR]"
            "[  RRR]"
            "[   YY]"
            "[  YYY]"
            "[GY YY]"
            "[   GG]"
            "[   CC]"
            "[   Cp]"
            "[  C p]"
            "[  C p]"};


    V2 Size;
    vector<int> IdTexs;
    int IdTex;
    int NumberLife = 3;
    V2 Pos = V2(50, 45);
    bool hasKey = false;

    void takeKey() {
        hasKey = true;
    }

    void useKey() {
        hasKey = false;
    }
};

struct _Key {
    string texture =
            "[     O O         OOOO ]"
            "[     O O   O    O    O]"
            "[   OOOOOOOOOOOOOO    O]"
            "[                O    O]"
            "[                 OOOO ]";


    V2 Size;
    int IdTex;
    V2 Pos = V2(440, 450);

    void disappear() {

    }
};

struct _CollisionMur {
    bool p_up;
    bool p_down;
    bool p_left;
    bool p_right;
};

struct _Chest {
    vector<string> textures =
            {"[                     ]"
             "[KKbbbbbbbbbbbbbbbbbKK]"
             "[KbbbbbbbbbbbbbbbbbbbK]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bKKKKKKKKKKKKKKKKKKKb]"
             "[bbbbbbbbbbObbbbbbbbbb]"
             "[bbb   bb OKO bb   bbb]"
             "[bbb   bb OKO bb   bbb]"
             "[bbbbbbbbbbObbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]",
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[KKKKKKKKKKKKKKKKKKKKK]"
             "[KKKKKKKKKKKKKKKKKKKKK]"
             "[KKKKKKRRRRRRRRRKKKKKK]"
             "[bKKKKRRRRRRRRRRRKKKKb]"
             "[bKKKRRRRRRRRRRRRRKKKb]"
             "[bKKKKRRRRRRRRRRRKKKKb]"
             "[bKKKKKRRRRRRRRRKKKKKb]"
             "[bKKKKKRRRRRRRRRKKKKKb]"
             "[bKKKKKKRRRRRRRKKKKKKb]"
             "[bKKKKKKKKRRRKKKKKKKKb]"
             "[bbbbbbbbbbRbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"
             "[bbbbbbbbbbbbbbbbbbbbb]"};

    V2 Size;
    vector<int> IdTexs;
    int IdTex;
    V2 Pos = V2(45, 530);

    void disappear() {
        Size = Size * 0;
        Pos = Pos * 0;
    }
};

struct mouseEvent { int x; int y; bool clicked; };

struct _Momie {

    vector<string> textures = {
            "[WWWWW]"
            "[WRWRW]"
            "[WWWWW]"
            "[OOO  ]"
            "[WWW  ]"
            "[WW OK]"
            "[Wb   ]"
            "[bWb  ]"
            "[WW   ]"
            "[W b  ]"
            "[b W  ]"
    };

    V2 Size;
    vector<int> IdTexs;
    int IdTex;
    V2 Dir = V2(0, 1);
    V2 Pos = V2(400, 450);

    bool CollisionMurMomie;
    V2 DirPossibles[4] = {V2(0, 1), V2(1, 0), V2(0, -1), V2(-1, 0)};

};

struct _Trap {

    vector<string> textures = {"[     ]"
                               "[     ]"
                               "[     ]",
                               "[R R R]"
                               "[R   R]"
                               "[R R R]"};

    V2 Size;
    vector<int> IdTexs;
    int IdTex;
    V2 Pos = V2(400, 450);
    bool triggered = false;

    void appear(){
        IdTex = IdTexs.at(1);
    }

    void effect (_Heros * heros){
        if (!triggered){
            heros->NumberLife--;
        }
    }
};

struct _GameData {

    string Map =
            "MMMMMMMMMMMMMMM"
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

    int Lpix = 40;  // largeur en pixels des cases du labyrinthe
    int LMap = 15;  // largeur de la Map en nombre de case
    int HMap = 15;  //Hauteur de la Map en nombre de case

    //indique la pr�sence d'un mur � la case (x,y)
    bool Mur(int x, int y) { return Map[(LMap - y - 1) * HMap + x] == 'M'; }

    bool Mur(V2 cell) { return Mur(cell.x, cell.y); }

    V2 pxToCoor(int x, int y) { return V2((int) x / Lpix, (int) y / Lpix); }

    V2 pxToCoor(V2 coor) { return pxToCoor((int) coor.x / Lpix, (int) coor.y / Lpix); }

    V2 coorToPx(int x, int y) { return V2(x * Lpix + Lpix / 2, y * Lpix + Lpix / 2); }

    V2 coorToPx(V2 coor) { return coorToPx(coor.x, coor.y); }

    _Heros Heros;   // data du h�ros
    _Key Key;
    _Chest Chest;
    _CollisionMur Collision;
    int Difficulty = 0;
    vector<_Momie> Momies;
    vector<_Trap> Traps;

    string ecran;
    int nbFrames = 0;

    _GameData() {}
};

_GameData G;
mouseEvent MS;

/// ACCEUIL ///
string gestion_ecran_accueil() {
    V2 titleStart = V2(150, 450);
    V2 buttonStart = V2(200, 300);
    V2 buttonStartSize = V2(200, 70);
    V2 buttonOptions = V2(240, 250);
    V2 buttonOptionsSize = V2(100, 40);


    G2D::ClearScreen(Color::Black);
    G2D::DrawStringFontRoman(titleStart, "The Labyrinth", 50, 4.5, Color::White);
    G2D::DrawRectangle(buttonStart, buttonStartSize, Color::Red, true);
    G2D::DrawStringFontMono(V2(buttonStart.x + 30, buttonStart.y + 30), "Start Game", 20, 3, Color::White);
    G2D::DrawRectangle(buttonOptions, buttonOptionsSize, Color::Gray, true);
    G2D::DrawStringFontMono(V2(buttonOptions.x + 10, buttonOptions.y + 15), "Options", 15, 2, Color::White);
    G2D::Show();

    G2D::GetMouseButtonInfo(0, MS.clicked, MS.x, MS.y);

    // Start button
    if (MS.clicked == true) {
        if (MS.x > buttonStart.x && MS.x < buttonStart.x + buttonStartSize.x) {
            if (MS.y > buttonStart.y && MS.y < buttonStart.y + buttonStartSize.y) {
                cout << "start button clicked" << endl;
                return "INIT_PARTIE";
            }
        }
    }
    /*
    if (buttonClicked(MS.clicked, MS.x, MS.y, buttonStart, buttonStartSize)) {
        cout << "start button clicked" << endl;
        return "INIT_PARTIE";
    }
    */


    // Options button
    if (MS.clicked == true) {
        if (MS.x > buttonOptions.x && MS.x < buttonOptions.x + buttonOptionsSize.x) {
            if (MS.y > buttonOptions.y && MS.y < buttonOptions.y + buttonOptionsSize.y) {
                cout << "options button clicked" << endl;
                return "ECRAN_OPTIONS";
            }
        }
    }
    /*
    if (button options cliked) return "ECRAN_OPTIONS";
    if (button startGame cliked) return "INIT_PARTIE";
    */

    return "ECRAN_ACCEUIL";
}

/// OPTIONS ///
string gestion_ecran_options() {
    V2 titleOptions = V2(150, 450);
    // Buttons : Music level
    V2 buttonPlus = V2(250, 300);
    V2 buttonMinus = V2(310, 300);
    V2 buttonP_MSize = V2(30, 30);
    // Button : Game's level of difficulty
    V2 buttonDifficulty = V2(320, 230);
    V2 buttonDifficultysSize = V2(80, 40);
    // Return Button
    V2 returnButton = V2(10, 540);
    V2 returnButtonSize = V2(40, 30);


    G2D::ClearScreen(Color::Black);

    G2D::DrawStringFontRoman(titleOptions, "OPTIONS", 40, 3, Color::Gray);
    G2D::DrawStringFontMono(V2(buttonPlus.x - 180, buttonPlus.y + 10), "Music level", 20, 1, Color::White);
    G2D::DrawRectangle(buttonPlus, buttonP_MSize, Color::Blue, true);
    G2D::DrawStringFontMono(V2(buttonPlus.x + 5, buttonPlus.y + 5), "+", 30, 4, Color::White);
    G2D::DrawRectangle(buttonMinus, buttonP_MSize, Color::Blue, true);
    G2D::DrawStringFontMono(V2(buttonMinus.x + 5, buttonMinus.y + 5), "-", 30, 4, Color::White);

    G2D::DrawRectangle(buttonDifficulty, buttonDifficultysSize, Color::Red, true);
    G2D::DrawStringFontMono(V2(buttonDifficulty.x - 250, buttonDifficulty.y + 10), "Difficulty level", 20, 1, Color::White);
    G2D::DrawStringFontMono(V2(buttonDifficulty.x + 15, buttonDifficulty.y + 15), "HARD", 20, 2, Color::White);

    G2D::DrawRectangle(returnButton, returnButtonSize, Color::Red, true);
    G2D::DrawStringFontMono(V2(returnButton.x + 5, returnButton.y + 10), "<-", 20, 2, Color::White);

    G2D::Show();

    G2D::GetMouseButtonInfo(0, MS.clicked, MS.x, MS.y);

    // + button
    if (MS.clicked == true) {
        if (MS.x > buttonPlus.x && MS.x < buttonPlus.x + buttonP_MSize.x) {
            if (MS.y > buttonPlus.y && MS.y < buttonPlus.y + buttonP_MSize.y) {
                cout << "Music level increased" << endl;
                // Augmente le niveau de la musique du jeu
            }
        }
    }

    // - button
    if (MS.clicked == true) {
        if (MS.x > buttonMinus.x && MS.x < buttonMinus.x + buttonP_MSize.x) {
            if (MS.y > buttonMinus.y && MS.y < buttonMinus.y + buttonP_MSize.y) {
                cout << "Music level decreased" << endl;
                // Baisse le niveau de la musique du jeu
            }
        }
    }

    // Difficulty level button
    if (MS.clicked == true) {
        if (MS.x > buttonDifficulty.x && MS.x < buttonDifficulty.x + buttonDifficultysSize.x) {
            if (MS.y > buttonDifficulty.y && MS.y < buttonDifficulty.y + buttonDifficultysSize.y) {
                cout << "Hard level of difficulty selected" << endl;
                G.Difficulty++;
            }
        }
    }

    // Return to "acceuil" button
    if (MS.clicked == true) {
        if (MS.x > returnButton.x && MS.x < returnButton.x + returnButtonSize.x) {
            if (MS.y > returnButton.y && MS.y < returnButton.y + returnButtonSize.y) {
                cout << "Return to home page" << endl;
                return "ECRAN_ACCEUIL";
            }
        }
    }

    return "ECRAN_OPTIONS";
}


/// GAME OVER ///
string gestion_GameOver() {
    V2 titleStart = V2(150, 300);

    G2D::ClearScreen(Color::Black);
    G2D::DrawStringFontMono(titleStart, "Game Over...", 50, 4.5, Color::White);
    G2D::DrawRectangle(V2(10, 10), V2(10, 10), Color::Red, false);
    G2D::Show();

    // Wait 3 seconds
    sleep_for(3000ms);
    return "ECRAN_ACCEUIL";
}

string gestion_win() {
    sleep_for(3000ms);

    V2 titleStart = V2(150, 300);
    G2D::ClearScreen(Color::Cyan);
    G2D::DrawStringFontMono(titleStart, "You Win !!!", 50, 4.5, Color::White);
    G2D::DrawRectangle(V2(10, 10), V2(10, 10), Color::Red, false);
    G2D::Show();

    // Wait 3 seconds
    sleep_for(3000ms);
    return "ECRAN_ACCEUIL";
}


// print particulier
std::ostream &operator<<(std::ostream &os, const _CollisionMur &a) {
    os << "\n{" << "\n\tUP:" << a.p_up << "\n\tDOWN:" << a.p_down << "\n\tLEFT:" << a.p_left << "\n\tRIGHT:"
       << a.p_right << "}\n";
    return os;
}

//utiles
void debug() {
    //active le noclip mode(passe a travers les murs)
    if (G2D::IsKeyPressed(Key::C)) noclip = true;
    else noclip = false;
    if (G2D::IsKeyPressed(Key::H)) hitbox = true;
    else hitbox = false;
}

//Collision
bool hitboxtouch(V2 posObj1, V2 sizeObj1, V2 posObj2, V2 sizeObj2) {
    return (posObj1.x <= posObj2.x + sizeObj2.x &&
            posObj1.x + sizeObj1.x >= posObj2.x &&
            posObj1.y <= posObj2.y + sizeObj2.y &&
            sizeObj1.y + posObj1.y >= posObj2.y);
}

bool collisionHeroClef(_Heros *heros, _Key *key) {
    return hitboxtouch(heros->Pos, heros->Size, key->Pos, key->Size);
}

bool collisionHeroChest(_Heros *heros, _Chest *chest) {
    return hitboxtouch(heros->Pos, heros->Size, chest->Pos, chest->Size);
}

bool collisionHeroMomies(_Heros *heros, vector<_Momie> momiesData) {
    for (int i = 0; i < G.Difficulty; i++)
        if (hitboxtouch(heros->Pos, heros->Size, momiesData[i].Pos, momiesData[i].Size))
            return true;
    return false;
}

// gestion du heros
void updateCollisionAvecUnMur(_GameData &gameData) {
    _Heros &heros = gameData.Heros;
    _CollisionMur &collision = gameData.Collision;

    float offset = 1;
    collision.p_up =
            gameData.Mur(gameData.pxToCoor(heros.Pos.x, heros.Pos.y + heros.Size.y + offset)) || gameData.Mur(
                    gameData.pxToCoor(heros.Pos.x + heros.Size.x, heros.Pos.y + heros.Size.y + offset));
    collision.p_down = gameData.Mur(gameData.pxToCoor(heros.Pos.x, heros.Pos.y - offset)) ||
                       gameData.Mur(gameData.pxToCoor(heros.Pos.x + heros.Size.x, heros.Pos.y - offset));
    collision.p_left = gameData.Mur(gameData.pxToCoor(heros.Pos.x - offset, heros.Pos.y)) ||
                       gameData.Mur(gameData.pxToCoor(heros.Pos.x - offset, heros.Pos.y + heros.Size.y));
    collision.p_right = gameData.Mur(gameData.pxToCoor(heros.Pos.x + heros.Size.x + offset, heros.Pos.y)) ||
                        gameData.Mur(gameData.pxToCoor(heros.Pos.x + heros.Size.x + offset,
                                                       heros.Pos.y + heros.Size.y));
}

void updateCollisionAvecUnMur(_GameData &gameData, _Momie *M) {

    float offset = 1;
    if (M->Dir == V2(0, 1))
        M->CollisionMurMomie =
        gameData.Mur(gameData.pxToCoor(M->Pos.x, M->Pos.y + M->Size.y + offset))
        || gameData.Mur(gameData.pxToCoor(M->Pos.x + M->Size.x, M->Pos.y + M->Size.y + offset));

    else if (M->Dir == V2(0, -1))
        M->CollisionMurMomie =
        gameData.Mur(gameData.pxToCoor(M->Pos.x, M->Pos.y - offset))
        || gameData.Mur(gameData.pxToCoor(M->Pos.x + M->Size.x, M->Pos.y - offset));

    else if (M->Dir == V2(-1, 0))
        M->CollisionMurMomie =
        gameData.Mur(gameData.pxToCoor(M->Pos.x - offset, M->Pos.y))
        || gameData.Mur(gameData.pxToCoor(M->Pos.x - offset, M->Pos.y + M->Size.y));

    else
        M->CollisionMurMomie =
        gameData.Mur(gameData.pxToCoor(M->Pos.x + M->Size.x + offset, M->Pos.y))
        || gameData.Mur(gameData.pxToCoor(M->Pos.x + M->Size.x + offset, M->Pos.y + M->Size.y));

}

bool canGoUp(_CollisionMur collision) {
    return !collision.p_up || noclip;
}

bool canGoDown(_CollisionMur collision) {
    return !collision.p_down || noclip;
}

bool canGoLeft(_CollisionMur collision) {
    return !collision.p_left || noclip;
}

bool canGoRight(_CollisionMur collision) {
    return !collision.p_right || noclip;
}

bool canGoDir(bool collision) {
    return !collision;
}

void GestionDeplacementHeros() {
    updateCollisionAvecUnMur(G);
    _Heros *heroData = &G.Heros;
    if (G2D::IsKeyPressed(Key::UP)) {
        if (canGoUp(G.Collision))
            G.Heros.Pos.y++;
    }
    if (G2D::IsKeyPressed(Key::DOWN)) {
        if (canGoDown(G.Collision))
            G.Heros.Pos.y--;
    }
    if (G2D::IsKeyPressed(Key::LEFT)) {
        if (canGoLeft(G.Collision)) {
            G.Heros.IdTex = (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() % 1000 <= 500)
                            ? G.Heros.IdTexs.at(3) : G.Heros.IdTexs.at(2);
            G.Heros.Pos.x--;
        }
    }
    if (G2D::IsKeyPressed(Key::RIGHT)) {
        if (canGoRight(G.Collision)) {
            G.Heros.IdTex = (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() % 1000 <= 500)
                            ? G.Heros.IdTexs.at(1) : G.Heros.IdTexs.at(0);
            G.Heros.Pos.x++;
        }
    }

}

void GestionDeplacementMomies() {
    int rd = 0;
    for (int i = 0; i < G.Difficulty; i++) {
        updateCollisionAvecUnMur(G, &G.Momies[i]);

        // calcul de la nouvelle position
        V2 newPos = G.Momies[i].Pos + G.Momies[i].Dir;

        // test pour savoir si on a une collision avec un mur
        if (canGoDir(G.Momies[i].CollisionMurMomie))
            G.Momies[i].Pos = newPos;
        else {
            srand((unsigned) time(nullptr));
            rd = (rand() + rd) % 4;
            G.Momies[i].Dir = G.Momies[i].DirPossibles[rd];
        }
    }
}

int gestion_jeu() {
    _Heros *heroData = &G.Heros;
    _Key *keyData = &G.Key;
    _Chest *chestData = &G.Chest;
    vector<_Momie> *momiesData = &G.Momies;

    debug();
    // le héros
    GestionDeplacementHeros();    // lecture du clavier / test mur

    if (collisionHeroClef(heroData, keyData)) {
        heroData->takeKey();
        keyData->disappear();
    }

    if (collisionHeroChest(heroData, chestData)) {
        if (heroData->hasKey) {
            heroData->useKey();
            chestData->IdTex = chestData->IdTexs[1];
            return 2; // victoire
        }
    }

    // les momies
    GestionDeplacementMomies();

    if (collisionHeroMomies(heroData, *momiesData)) {
        G.Heros.NumberLife = G.Heros.NumberLife > 0 ? G.Heros.NumberLife - 1 : 0;
        G.Heros.Pos = V2(50, 45);
    }

    // détection si partie terminée
    if (heroData->NumberLife <= 0) {
        return 1; // mort
    }
    return 0; //jeu
}

//prof

void AssetsInit() {
    // Size pass� en ref et texture en param

    G.Difficulty = (G.Difficulty <= 0) ? 3: G.Difficulty;

    //hero
    for (const string &t: G.Heros.textures) G.Heros.IdTexs.push_back(G2D::InitTextureFromString(G.Heros.Size, t));
    G.Heros.IdTex = G.Heros.IdTexs.at(0);
    G.Heros.Size = G.Heros.Size * 2;
    G.Heros.Pos = V2(50, 45);
    G.Heros.NumberLife = 3;
    G.Heros.hasKey = false;

    //clef
    G.Key.IdTex = G2D::InitTextureFromString(G.Key.Size, G.Key.texture);
    G.Key.Size = G.Key.Size * 1.5;
    G.Key.Pos = V2(440, 450);

    //coffre
    for (const string &t: G.Chest.textures) G.Chest.IdTexs.push_back(G2D::InitTextureFromString(G.Chest.Size, t));
    G.Chest.IdTex = G.Chest.IdTexs.at(0);
    G.Chest.Size = G.Chest.Size * 1.5;

    //Momie
    for (int i = 0; i < G.Difficulty; i++) {
        _Momie momieData;
        G.Momies.push_back(momieData);
    }

    for (int i = 0; i < G.Difficulty; i++) {
        for (const string &t: G.Momies[i].textures)
            G.Momies[i].IdTexs.push_back(G2D::InitTextureFromString(G.Momies[i].Size, t));
        G.Momies[i].IdTex = G.Momies[i].IdTexs.at(0);
        G.Momies[i].Size = G.Momies[i].Size * 2;
        G.Momies[i].Pos = V2(400, 450);
    }
}

void render_game() {
    G2D::ClearScreen(Color::Black);

    for (int x = 0; x < 15; x++)
        for (int y = 0; y < 15; y++) {
            int xx = x * G.Lpix;
            int yy = y * G.Lpix;
            if (G.Mur(x, y))
                G2D::DrawRectangle(V2(xx, yy), V2(G.Lpix, G.Lpix), Color::Blue, true);
        }


    G2D::DrawStringFontMono(V2(550, 15), to_string(G.Heros.NumberLife), 20, 3, Color::White);

    // affichage du h�ro avec boite englobante et zoom x 2
    G2D::DrawRectWithTexture(G.Heros.IdTex, G.Heros.Pos, G.Heros.Size);
    if (hitbox) G2D::DrawRectangle(G.Heros.Pos, G.Heros.Size, Color::Red); //hitbox

    // affichage de la clef et de sa hitbox si la clef existe
    if (!G.Heros.hasKey)G2D::DrawRectWithTexture(G.Key.IdTex, G.Key.Pos, G.Key.Size);
    if (hitbox) G2D::DrawRectangle(G.Key.Pos, G.Key.Size, Color::Red);

    //affichage du coffre
    G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);
    if (hitbox) G2D::DrawRectangle(G.Chest.Pos, G.Chest.Size, Color::Red);

    for (int i = 0; i < G.Difficulty; i++) {
        if (hitbox) G2D::DrawRectangle(G.Momies[i].Pos, G.Momies[i].Size, Color::Red); //hitbox
        G2D::DrawRectWithTexture(G.Momies[i].IdTex, G.Momies[i].Pos, G.Momies[i].Size);
    }
    G2D::Show();
}

string InitPartie() {
    AssetsInit();
    return "ECRAN_JEU";
}

void render() {

    if (G.ecran == "ECRAN_ACCEUIL") {
        G.ecran = gestion_ecran_accueil();
    }

    if (G.ecran == "ECRAN_OPTIONS") {
        G.ecran = gestion_ecran_options();
    }

    if (G.ecran == "INIT_PARTIE") {
        G.ecran = InitPartie();
    }

    if (G.ecran == "ECRAN_JEU") {
        render_game();
    }

    if (G.ecran == "ECRAN_GAME_OVER") {
        G.ecran = gestion_GameOver();
    }

    if (G.ecran == "ECRAN_WIN") {
        render_game();
        G.ecran = gestion_win();
    }

}

void Logic() {
    if (G.ecran != "ECRAN_JEU")
        return;
    switch (gestion_jeu()) {
        case 0: G.ecran = "ECRAN_JEU"; break;
        case 1: G.ecran = "ECRAN_GAME_OVER"; break;
        case 2: G.ecran = "ECRAN_WIN"; break;
        default:;
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    G2D::InitWindow(argc, argv, V2(G.Lpix * 15, G.Lpix * 15), V2(200, 200), string("Labyrinthe"));
    G.ecran = "ECRAN_ACCEUIL";
    G2D::Run(Logic, render);
}
 