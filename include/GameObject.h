#pragma once

#include <raylib.h>

class GameObject {

protected:

    // Temporary location to store image
    Image image = { 0 };

public:
    Vector2 gridLocation;
    Texture2D texture;
    GameObject(Vector2 gridLocation, const char* imagePath) : gridLocation(gridLocation) {
        image = LoadImage(imagePath);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    

    GameObject(Vector2 gridLocation, Image image) : gridLocation(gridLocation) {
        // Image should be unloaded from outside of this scope
        texture = LoadTextureFromImage(image);
    }

    ~GameObject() {
        UnloadTexture(texture);
    }

    Vector2 GetScreenLocation();

    virtual void Draw() {}
};