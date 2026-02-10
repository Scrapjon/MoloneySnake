#include "Snake.h"

void Snake::Draw() {
	for (Vector2& point : body) {
		Rectangle segment = Rectangle{ (point.x * cellSize) + borderPadding, (point.y * cellSize) + borderPadding, cellSize, cellSize };
		DrawRectangleRounded(segment, 0.5, 6, secondaryColor);
	}
}

void Snake::Update() {

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

void Snake::Reset()
{
	body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
}
