#include "Food.h"

Food::Food(std::deque<Vector2> snakeBody)
{
	Image image = LoadImage("assets/Food.png");
	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	position = GenerateRandomPos(snakeBody);
}

Food::~Food()
{
	UnloadTexture(texture);
}

void Food::Draw()
{
	DrawTexture(texture, (position.x * cellSize) + borderPadding, (position.y * cellSize) + borderPadding, WHITE);
}

Vector2 Food::GenerateRandomCell()
{
	const float x = GetRandomValue(0, cellCount - 1);
	const float y = GetRandomValue(0, cellCount - 1);
	return { x, y };
}

Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody)
{
	Vector2 position = GenerateRandomCell();

	while (ElementInDeque(position, snakeBody)) {
		position = GenerateRandomCell();
	};

	return position;
}
