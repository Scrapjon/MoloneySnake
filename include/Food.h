#pragma once
#include "Globals.h"

class Food {
public:
	Vector2 position;
	Texture2D texture;

	Food(std::deque<Vector2> snakeBody);

	~Food();

	void Draw();

	Vector2 GenerateRandomCell();

	Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
};