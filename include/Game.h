#pragma once
#include <cmath>
#include "Globals.h"
#include "Snake.h"
#include "Food.h"



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

	Game();

	~Game();

	void StartGame();

	void StartMusic();

	void UpdateMusic();

	void Draw();

	void Update();

	void CheckCollisionWithFood();

	void CheckCollisionWithEdges();

	void CheckCollisionWithTail();

	void GameOver();

	void DisplayGameOver();

};