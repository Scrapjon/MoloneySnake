#include "Game.h"

Game::Game()  {

    InitWindow(screenWidth, screenHeight, "Moloney Snake!");
    SetTargetFPS(60);

    // Initialise Objects
    food = new Food();


}

void Game::GameLoop() {


    while (!WindowShouldClose()) {

        // Update the display
        BeginDrawing();
        ClearBackground(BLACK);
        if (food)
            food->Draw();

        EndDrawing();
    }
}

Game::~Game() {
    delete food;

    // Cleanup
    CloseWindow();
}
