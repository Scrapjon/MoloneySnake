#include "Game.h"

#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, const char** argv) {


	InitWindow(2 * borderPadding + screenSize, 2 * borderPadding + screenSize, "Moloney Snake!");
	SetTargetFPS(60);
	Game game = Game();

	game.StartMusic();

	while (!WindowShouldClose()) {

		

		BeginDrawing();

		if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.lastUpdateDirection.y != 1) {
			game.snake.direction = { 0, -1 };
			if (!game.running)
				game.StartGame();
		}

		if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.lastUpdateDirection.y != -1) {
			game.snake.direction = { 0, 1 };
			if (!game.running)
				game.StartGame();
		}
		if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.lastUpdateDirection.x != 1) {
			game.snake.direction = { -1, 0 };
			if (!game.running)
				game.StartGame();
		}
		if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.lastUpdateDirection.x != -1) {
			game.snake.direction = { 1, 0 };
			if (!game.running)
				game.StartGame();
		}
		if (EventTriggered(updateSpeed)) {
			game.Update();
		}

		
		game.UpdateMusic();

		// Drawing
		ClearBackground(primaryColor);
		
		DrawRectangleLinesEx(border, 5, secondaryColor);

		DrawText("MOLONEY SNAKE", borderPadding - 5, 20, 40, secondaryColor);

		if (game.score == 1) {
			DrawText(TextFormat("%i Moloney Snack", game.score), borderPadding - 5, borderPadding + screenSize + 10, 40, secondaryColor);
		}
		else {
			DrawText(TextFormat("%i Moloney Snacks", game.score), borderPadding - 5, borderPadding + screenSize + 10, 40, secondaryColor);
		}
		
		DrawText(TextFormat("High Score: %i", game.highScore), screenSize - 250, borderPadding + screenSize + 10, 40, secondaryColor);

		game.Draw();

		if (game.gameOver) {
			game.DisplayGameOver();
		}


		EndDrawing();

		

	}

	CloseWindow();
	return 0;
}
