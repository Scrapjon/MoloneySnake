#pragma once

#include <iostream>
#include <raylib.h>
#include "Food.h"
#include "Globals.h"



class Game {

public:

    Food* food = nullptr;

    Game();
    void GameLoop();


    ~Game();
};