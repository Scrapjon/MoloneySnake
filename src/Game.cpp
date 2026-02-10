#include "Game.h"

Game::Game()
{
	InitAudioDevice();
	music = LoadMusicStream("assets/sounds/MoloneySnake.wav");
	eatSound = LoadSound("assets/sounds/EatSound.wav");
	loseSound = LoadSound("assets/sounds/LoseSound.wav");
}

Game::~Game()
{
	UnloadMusicStream(music);
	UnloadSound(eatSound);
	UnloadSound(loseSound);
	CloseAudioDevice();
}

void Game::StartGame()
{
	score = 0;
	running = true;
	gameOver = false;
}

void Game::StartMusic()
{
	PlayMusicStream(music);
}

void Game::UpdateMusic()
{
	UpdateMusicStream(music);
}

void Game::Draw() 
{
	food.Draw();
	snake.Draw();
}

void Game::Update() {
	if (!running) return;

	snake.Update();
	CheckCollisionWithFood();
	CheckCollisionWithEdges();
	CheckCollisionWithTail();
}

void Game::CheckCollisionWithFood()
{
	if (Vector2Equals(snake.body[0], food.position)) {
		food.position = food.GenerateRandomPos(snake.body);
		snake.addSegment = true;
		score++;
		PlaySound(eatSound);
		updateSpeed = 0.2 / (std::max(std::floor(score * 0.25), 1.0));
	}
}

void Game::CheckCollisionWithEdges()
{
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

void Game::CheckCollisionWithTail()
{
	// Can never collide with 0th or 1st index
	for (size_t i = 2; i < snake.body.size(); i++) {
		if (Vector2Equals(snake.body[i], snake.body[0])) {
			GameOver();
			break;
		}
	}
}

void Game::GameOver()
{
	gameOver = true;
	PlaySound(loseSound);
	snake.Reset();
	food.position = food.GenerateRandomPos(snake.body);
	running = false;
	highScore = std::max(score, highScore);
	updateSpeed = defaultUpdateSpeed;
}

void Game::DisplayGameOver()
{
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
