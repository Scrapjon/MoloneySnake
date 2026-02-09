#include <stdlib.h>
#include "Globals.h"
#include "GameObject.h"
#include "generated_assets/Food_Image.h"



class Food : GameObject {

public:
    Food() : GameObject(GenerateRandomPos(), LOAD_OBJECT_IMAGE(FOOD)) {
        UnloadImage(image);
    }

    Vector2 GenerateRandomPos() {
        const float x = static_cast<float>(GetRandomValue(0, cellNum-1));
        const float y = static_cast<float>(GetRandomValue(0, cellNum - 1));
        return { x, y };
    }

    void SetNewLocation() {
        gridLocation = GenerateRandomPos();
    }
    
    virtual void Draw() override;

};