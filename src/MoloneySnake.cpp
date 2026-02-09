#include <raylib.h>
#include <raymath.h>
#include <deque>
#include <cmath>
#include <iostream>

#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

const static Color primaryColor = RED;
const static Color secondaryColor = BLACK;

const static int screenSize = 750; // Square window
const static int cellSize = 30;
const static int cellCount = 25;
const static int borderPadding = 75;

const static double defaultUpdateSpeed = 0.2;
static double updateSpeed = defaultUpdateSpeed;

const static Rectangle border = Rectangle{ borderPadding - 5, borderPadding - 5, screenSize + 10, screenSize + 10 };

static double lastUpdateTime = 0;

static bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

static bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
	for (size_t i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element))
			return true;
	}
	return false;
}

class Food {
public:
	Vector2 position;
	Texture2D texture;

	Food(std::deque<Vector2> snakeBody) {
		Image image = LoadImage("assets/Food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos(snakeBody);
	}

	~Food() {
		UnloadTexture(texture);
	}

	void Draw() {
		DrawTexture(texture, (position.x * cellSize) + borderPadding, (position.y * cellSize) + borderPadding, WHITE);
	}

	Vector2 GenerateRandomCell() {
		const float x = GetRandomValue(0, cellCount - 1);
		const float y = GetRandomValue(0, cellCount - 1);
		return { x, y };
	}

	Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {
		Vector2 position = GenerateRandomCell();

		while (ElementInDeque(position, snakeBody)) {
			position = GenerateRandomCell();
		};

		return position;
	}
};

class Snake {
public:
	std::deque<Vector2> body = { Vector2{ 6, 9 }, Vector2{ 5, 9 }, Vector2{ 4, 9 } };
	Vector2 direction = { 0, -1 };
	Vector2 lastUpdateDirection = { 0, 0 };
	bool addSegment = false;

	void Draw()
	{
		for (Vector2& point : body) {
			Rectangle segment = Rectangle{ (point.x * cellSize) + borderPadding, (point.y * cellSize) + borderPadding, cellSize, cellSize };
			DrawRectangleRounded(segment, 0.5, 6, secondaryColor);
		}
	}

	void Update() {

		Vector2 nextLocation = Vector2Add(body[0], direction);

		if (!addSegment)
			body.pop_back();
		else addSegment = false;
		lastUpdateDirection = direction;
		
#ifndef EVIL_EDGES
		if (nextLocation.x < 0) while (nextLocation.x < cellCount) nextLocation.x += cellCount;
		if (nextLocation.y < 0) while (nextLocation.y < cellCount) nextLocation.y += cellCount;
		nextLocation.x = static_cast<float>(fmod(nextLocation.x, cellCount));
		nextLocation.y = static_cast<float>(fmod(nextLocation.y, cellCount));
#endif // !EVIL_EDGES
		body.push_front(nextLocation);
	}

	void Reset() {
		body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
	}

};

class Game {
public:

	Snake snake = Snake();
	Food food = Food(snake.body);
	int score = 0;
	int highScore = 0;

	bool running = false;
	bool gameOver = false;

	Music music;
	Sound eatSound;
	Sound loseSound;

	Game() {
		InitAudioDevice();
		music = LoadMusicStream("assets/sounds/MoloneySnake.wav");
		eatSound = LoadSound("assets/sounds/EatSound.wav");
		loseSound = LoadSound("assets/sounds/LoseSound.wav");
	}

	~Game() {
		UnloadMusicStream(music);
		UnloadSound(eatSound);
		UnloadSound(loseSound);
		CloseAudioDevice();
	}

	void StartGame() {
		score = 0;
		running = true;
		gameOver = false;
	}

	void StartMusic() {
		PlayMusicStream(music);
	}

	void UpdateMusic() {
		UpdateMusicStream(music);
	}

	void Draw() {
		food.Draw();
		snake.Draw();
	};

	void Update() {
		if (!running) return;

		snake.Update();
		CheckCollisionWithFood();
		CheckCollisionWithEdges();
		CheckCollisionWithTail();
	}

	void CheckCollisionWithFood() {
		if (Vector2Equals(snake.body[0], food.position)) {
			food.position = food.GenerateRandomPos(snake.body);
			snake.addSegment = true;
			score++;
			PlaySound(eatSound);
			updateSpeed = 0.2 / (std::max(std::floor(score * 0.25), 1.0));
		}
	}

	void CheckCollisionWithEdges() {
#ifdef EVIL_EDGES
		if (snake.body[0].x == cellCount || snake.body[0].x == -1)
		{
			GameOver();
		}
		if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
			GameOver();
		}
#endif

	}

	void CheckCollisionWithTail() {

		// Can never collide with 0th or 1st index
		for (size_t i = 2; i < snake.body.size(); i++) {
			if (Vector2Equals(snake.body[i], snake.body[0])) {
				GameOver();
				break;
			}
		}
	}
	
	void GameOver() {
		gameOver = true;
		PlaySound(loseSound);
		snake.Reset();
		food.position = food.GenerateRandomPos(snake.body);
		running = false;
		highScore = std::max(score, highScore);
		updateSpeed = defaultUpdateSpeed;
	}

	void DisplayGameOver() {
		const char* gameOverMessage = "GAME OVER!";
		const int gameOverFontSize = 40;

		const char* scoreMessage = TextFormat("YORE SCORE WAS %i!", score);
		const int scoreFontSize = 30;

		const float messageSpacing = 1.0f;

		const Font font = GetFontDefault();
		const Vector2 gameOverMessageSize = MeasureTextEx(font, gameOverMessage, gameOverFontSize, messageSpacing);
		const Vector2 gameOverMessagePos = Vector2{ (screenSize + gameOverMessageSize.x) / 2, (screenSize + gameOverMessageSize.y) / 2 };

		const Vector2 scoreMessageSize = MeasureTextEx(font, scoreMessage, scoreFontSize, messageSpacing);
		const Vector2 scoreMessagePos = Vector2{ (screenSize + scoreMessageSize.x) / 2, ((screenSize + scoreMessageSize.y) / 2) + gameOverMessageSize.y };

		DrawTextEx(font, gameOverMessage, gameOverMessagePos, gameOverFontSize, messageSpacing, secondaryColor);

		DrawTextEx(font, scoreMessage, scoreMessagePos, scoreFontSize, messageSpacing, secondaryColor);


	}
};

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
