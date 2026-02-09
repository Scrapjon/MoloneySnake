#pragma once
#include <raylib.h>
#include <deque>
#include "GameObject.h"

class Snake : GameObject {

public:
	std::deque<Vector2> body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} }
};