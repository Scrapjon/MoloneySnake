#pragma once
#include "Globals.h"

class Snake {
public:
	std::deque<Vector2> body = { Vector2{ 6, 9 }, Vector2{ 5, 9 }, Vector2{ 4, 9 } };
	Vector2 direction = { 0, -1 };
	Vector2 lastUpdateDirection = { 0, 0 };
	bool addSegment = false;

	void Draw();

	void Update();

	void Reset();

};