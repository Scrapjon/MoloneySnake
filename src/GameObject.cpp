#include "GameObject.h"
#include "Globals.h"

Vector2 GameObject::GetScreenLocation()
{
    return { gridLocation.x * cellSize, gridLocation.y * cellSize };
}
