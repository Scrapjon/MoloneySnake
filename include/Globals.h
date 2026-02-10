#pragma once

#include <raylib.h>
#include <raymath.h>
#include <deque>

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

static bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

static bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
	for (size_t i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element))
			return true;
	}
	return false;
}