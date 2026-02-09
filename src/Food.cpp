#include "Globals.h"
#include "Food.h"

void Food::Draw()
{
    const Vector2 screenLocation = GetScreenLocation();
    DrawTexture(texture, screenLocation.x, screenLocation.y, WHITE);
}